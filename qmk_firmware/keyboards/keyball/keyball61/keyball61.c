/*
Copyright 2021 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include <string.h>

#include "quantum.h"

#include "transactions.h"
#include "drivers/pmw3360/pmw3360.h"

//////////////////////////////////////////////////////////////////////////////

#define KEYBALL_CPI_DEFAULT 500

//////////////////////////////////////////////////////////////////////////////

#define TX_GETINFO_INTERVAL 500
#define TX_GETINFO_MAXTRY 10
#define TX_GETMOTION_INTERVAL 5

//////////////////////////////////////////////////////////////////////////////

typedef union {
    uint32_t raw;
    struct {
        uint8_t cpi:7;
    };
} keyball_config_t;

typedef struct {
    uint16_t vid;
    uint16_t pid;
    uint8_t  ballcnt;  // count of balls: support only 0 or 1, for now
} keyball_info_t;

typedef uint8_t keyball_motion_id_t;

typedef struct {
    int16_t x;
    int16_t y;
    uint8_t n;  // accumulative scan count after last consume.
} keyball_motion_t;

typedef uint16_t keyball_cpi_t;

//////////////////////////////////////////////////////////////////////////////

static bool this_have_ball = false;
static bool that_enable    = false;
static bool that_have_ball = false;

static keyball_motion_t this_motion = {0};
static keyball_motion_t that_motion = {0};

static uint16_t cpi_value   = KEYBALL_CPI_DEFAULT;
static bool     cpi_changed = false;

static bool scroll_mode = false;

static uint16_t       last_keycode;
static uint8_t        last_row;
static uint8_t        last_col;
static report_mouse_t last_mouse = {};

//////////////////////////////////////////////////////////////////////////////

// clang-format off
matrix_row_t matrix_mask[MATRIX_ROWS] = {
    0b01110111,
    0b01110111,
    0b01110111,
    0b11110111,
    0b11110111,
    0b01110111,
    0b01110111,
    0b01110111,
    0b11110111,
    0b11110111,
};
// clang-format on

static void adjust_rgblight_ranges(void) {
#ifdef RGBLIGHT_ENABLE
    // adjust RGBLIGHT's clipping and effect ranges
    uint8_t lednum_this = this_have_ball ? 34 : 37;
    uint8_t lednum_that = !that_enable ? 0 : that_have_ball ? 34 : 37;
    rgblight_set_clipping_range(is_keyboard_left() ? 0 : lednum_that, lednum_this);
    rgblight_set_effect_range(0, lednum_this + lednum_that);
#endif
}

static void adjust_board_as_this(void) {
    adjust_rgblight_ranges();

    keyball_config_t c;
    c.raw = eeconfig_read_kb();
    if (c.cpi != 0) {
        pointing_device_set_cpi(c.cpi * 100);
    }
}

static void adjust_board_on_primary(void) {
    adjust_rgblight_ranges();

#ifdef VIA_ENABLE
    // adjust layout options value according to current combination.
    bool left = is_keyboard_left();
    uint8_t layouts =
        (this_have_ball ? (left ? 0x02 : 0x01) : 0x00) |
        (that_have_ball ? (left ? 0x01 : 0x02) : 0x00);
    uint32_t curr = via_get_layout_options();
    uint32_t next = (curr & ~0x3) | layouts;
    if (next != curr) {
        via_set_layout_options(next);
    }
#endif
}

static void adjust_board_on_secondary(void) { adjust_rgblight_ranges(); }

//////////////////////////////////////////////////////////////////////////////

// add16 adds two int16_t with clipping.
static int16_t add16(int16_t a, int16_t b) {
    int16_t r = a + b;
    if (a >= 0 && b >= 0 && r < 0) {
        r = 32767;
    } else if (a < 0 && b < 0 && r >= 0) {
        r = -32768;
    }
    return r;
}

// incU8 increments a uint8_t with clipping.
static inline uint8_t incU8(uint8_t a) { return a < 0xff ? a + 1 : 0xff; }

// clip2int8 clips an integer fit into int8_t.
static inline int8_t clip2int8(int16_t v) { return (v) < -127 ? -127 : (v) > 127 ? 127 : (int8_t)v; }

static void motion_to_mouse_move(keyball_motion_t *m, report_mouse_t *r, bool is_left) {
    if (m->n == 0) {
        return;
    }
    r->x = clip2int8(m->y);
    r->y = clip2int8(m->x);
    if (is_left) {
        r->x = -r->x;
        r->y = -r->y;
    }
    // clear motion
    m->x = 0;
    m->y = 0;
    m->n = 0;
}

static void motion_to_mouse_scroll(keyball_motion_t *m, report_mouse_t *r, bool is_left) {
    if (m->n == 0) {
        return;
    }
    r->h = clip2int8(m->y);
    r->v = clip2int8(m->x);
    if (!is_left) {
        r->h = -r->h;
        r->v = -r->v;
    }
    // clear motion
    m->x = 0;
    m->y = 0;
    m->n = 0;
}

void pointing_device_driver_init(void) {
    this_have_ball = pmw3360_init();
    if (this_have_ball) {
        pmw3360_cpi_set(KEYBALL_CPI_DEFAULT);
        pmw3360_reg_write(pmw3360_Motion_Burst, 0);
    }
}

report_mouse_t pointing_device_driver_get_report(report_mouse_t rep) {
    // fetch from optical sensor.
    if (this_have_ball) {
        pmw3360_motion_t d = {0};
        if (pmw3360_motion_burst(&d)) {
            ATOMIC_BLOCK_FORCEON {
                this_motion.x = add16(this_motion.x, d.x);
                this_motion.y = add16(this_motion.y, d.y);
                this_motion.n = incU8(this_motion.n);
            }
        }
    }
    // report mouse event, if keyboard is primary.
    if (is_keyboard_master()) {
        bool is_left = is_keyboard_left();
        if (this_have_ball) {
            if (scroll_mode) {
                motion_to_mouse_scroll(&this_motion, &rep, is_left);
            } else {
                motion_to_mouse_move(&this_motion, &rep, is_left);
            }
            // dual ball
            if (that_have_ball) {
                motion_to_mouse_scroll(&this_motion, &rep, !is_left);
            }
        } else if (that_have_ball) {
            // only that ball
            if (scroll_mode) {
                motion_to_mouse_scroll(&that_motion, &rep, !is_left);
            } else {
                motion_to_mouse_move(&that_motion, &rep, !is_left);
            }
        }
    }
    return rep;
}

uint16_t pointing_device_driver_get_cpi(void) { return cpi_value; }

void pointing_device_driver_set_cpi(uint16_t cpi) {
    if (this_have_ball) {
        pmw3360_cpi_set(cpi);
        pmw3360_reg_write(pmw3360_Motion_Burst, 0);
    }
    cpi_value   = cpi;
    cpi_changed = true;
}

static void add_cpi(int16_t delta) {
    int16_t v = cpi_value + delta;
    if (v < 100) {
        v = 100;
    } else if (v > 12000) {
        v = 12000;
    }
    pointing_device_set_cpi(v);
}

//////////////////////////////////////////////////////////////////////////////

static void keyball_get_info_handler(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data) {
    keyball_info_t *that = (keyball_info_t *)in_data;
    if (that->vid == VENDOR_ID && that->pid == PRODUCT_ID) {
        that_enable    = true;
        that_have_ball = that->ballcnt > 0;
    }
    keyball_info_t info = {
        .vid     = VENDOR_ID,
        .pid     = PRODUCT_ID,
        .ballcnt = this_have_ball ? 1 : 0,
    };
    memcpy(out_data, &info, sizeof(info));
    adjust_board_on_secondary();
}

static void keyball_get_info_invoke(void) {
    static bool     negotiated = false;
    static uint32_t last_sync  = 0;
    static int      round      = 0;
    if (negotiated || timer_elapsed32(last_sync) < TX_GETINFO_INTERVAL) {
        return;
    }
    last_sync = timer_read32();
    round++;
    keyball_info_t req = {
        .vid     = VENDOR_ID,
        .pid     = PRODUCT_ID,
        .ballcnt = this_have_ball ? 1 : 0,
    };
    keyball_info_t recv = {0};
    if (!transaction_rpc_exec(KEYBALL_GET_INFO, sizeof(req), &req, sizeof(recv), &recv)) {
        if (round < TX_GETINFO_MAXTRY) {
            dprintf("keyball_get_info_invoke: missed #%d\n", round);
            return;
        }
    }
    negotiated = true;
    if (recv.vid == VENDOR_ID && recv.pid == PRODUCT_ID) {
        that_enable    = true;
        that_have_ball = recv.ballcnt > 0;
    }
    dprintf("keyball_get_info_invoke: negotiated #%d %d\n", round, that_have_ball);
    if (is_keyboard_master()) {
        adjust_board_on_primary();
    } else {
        adjust_board_on_secondary();
    }
}

static void keyball_get_motion_handler(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data) {
    if (this_have_ball && *((keyball_motion_id_t *)in_data) == 0) {
        *(keyball_motion_t *)out_data = this_motion;
        // clear motion
        this_motion.x = 0;
        this_motion.y = 0;
        this_motion.n = 0;
    }
}

static void keyball_get_motion_invoke(void) {
    static uint32_t last_sync = 0;
    if (!that_have_ball || that_motion.n != 0 || timer_elapsed32(last_sync) < TX_GETMOTION_INTERVAL) {
        return;
    }
    keyball_motion_id_t req  = 0;
    keyball_motion_t    recv = {0};
    if (transaction_rpc_exec(KEYBALL_GET_MOTION, sizeof(req), &req, sizeof(recv), &recv)) {
        ATOMIC_BLOCK_FORCEON { that_motion = recv; }
    } else {
        dprintf("keyball_get_motion_invoke: failed");
    }
    last_sync = timer_read32();
    return;
}

static void keyball_set_cpi_handler(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data) {
    if (this_have_ball) {
        pmw3360_cpi_set(*(keyball_cpi_t *)in_data);
        pmw3360_reg_write(pmw3360_Motion_Burst, 0);
    }
}

static void keyball_set_cpi_invoke(void) {
    if (!that_have_ball || !cpi_changed) {
        return;
    }
    keyball_cpi_t req = cpi_value;
    if (!transaction_rpc_send(KEYBALL_SET_CPI, sizeof(req), &req)) {
        return;
    }
    cpi_changed = false;
}

//////////////////////////////////////////////////////////////////////////////

#ifdef OLED_ENABLE

static const char *format_4d(int8_t d) {
    static char buf[5] = {0};  // max width (4) + NUL (1)
    char        lead   = ' ';
    if (d < 0) {
        d    = -d;
        lead = '-';
    }
    buf[3] = (d % 10) + '0';
    d /= 10;
    if (d == 0) {
        buf[2] = lead;
        lead   = ' ';
    } else {
        buf[2] = (d % 10) + '0';
        d /= 10;
    }
    if (d == 0) {
        buf[1] = lead;
        lead   = ' ';
    } else {
        buf[1] = (d % 10) + '0';
        d /= 10;
    }
    buf[0] = lead;
    return buf;
}

static char to_1x(uint8_t x) {
    x &= 0x0f;
    return x < 10 ? x + '0' : x + 'a' - 10;
}

#endif

void keyball_oled_render_ballinfo(void) {
#ifdef OLED_ENABLE
    // Format: `Ball:{ball#1 x}{ball#1 y}{ball#2 x}{ball#2 y}
    //
    // Output example:
    //
    //     Ball: -12  34   0   0
    //
    oled_write_P(PSTR("Ball:"), false);
    oled_write(format_4d(last_mouse.x), false);
    oled_write(format_4d(last_mouse.y), false);
    oled_write(format_4d(last_mouse.h), false);
    oled_write(format_4d(last_mouse.v), false);
    // CPI
    oled_write_P(PSTR("CPI :  "), false);
    oled_write(format_4d(cpi_value / 100), false);
    oled_write_P(PSTR("00  S"), false);
    oled_write_char(scroll_mode ? '1' : '0', false);
#endif
}

#ifdef OLED_ENABLE
// clang-format off
const char PROGMEM code_to_name[] = {
    'a', 'b', 'c', 'd', 'e', 'f',  'g', 'h', 'i',  'j',
    'k', 'l', 'm', 'n', 'o', 'p',  'q', 'r', 's',  't',
    'u', 'v', 'w', 'x', 'y', 'z',  '1', '2', '3',  '4',
    '5', '6', '7', '8', '9', '0',  'R', 'E', 'B',  'T',
    '_', '-', '=', '[', ']', '\\', '#', ';', '\'', '`',
    ',', '.', '/',
};
// clang-format on
#endif

void keyball_oled_render_keyinfo(void) {
#ifdef OLED_ENABLE
    // Format: `Key :  R{row}  C{col} K{kc}  '{name}`
    //
    // Where `kc` is lower 8 bit of keycode.
    // Where `name` is readable label for `kc`, valid between 4 and 56.
    //
    // It is aligned to fit with output of keyball_oled_render_ballinfo().
    // For example:
    //
    //     Key :  R2  C3 K06  'c
    //     Ball:   0   0   0   0
    //
    uint8_t keycode = last_keycode;

    oled_write_P(PSTR("Key :  R"), false);
    oled_write_char(to_1x(last_row), false);
    oled_write_P(PSTR("  C"), false);
    oled_write_char(to_1x(last_col), false);
    if (keycode) {
        oled_write_P(PSTR(" K"), false);
        oled_write_char(to_1x(keycode >> 4), false);
        oled_write_char(to_1x(keycode), false);
    }
    if (keycode >= 4 && keycode < 57) {
        oled_write_P(PSTR("  '"), false);
        char name = pgm_read_byte(code_to_name + keycode - 4);
        oled_write_char(name, false);
    } else {
        oled_advance_page(true);
    }
#endif
}

//////////////////////////////////////////////////////////////////////////////

void keyboard_post_init_kb(void) {
    // register transaction handlers on secondary.
    if (!is_keyboard_master()) {
        transaction_register_rpc(KEYBALL_GET_INFO, keyball_get_info_handler);
        transaction_register_rpc(KEYBALL_GET_MOTION, keyball_get_motion_handler);
        transaction_register_rpc(KEYBALL_SET_CPI, keyball_set_cpi_handler);
    }
    adjust_board_as_this();
    keyboard_post_init_user();
}

void housekeeping_task_kb(void) {
    if (is_keyboard_master()) {
        keyball_get_info_invoke();
        keyball_get_motion_invoke();
        keyball_set_cpi_invoke();
    }
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // store last keycode, row, and col for OLED
    last_keycode = keycode;
    last_row     = record->event.key.row;
    last_col     = record->event.key.col;

    if (!process_record_user(keycode, record)) {
        return false;
    }

    switch (keycode) {
        // process KC_MS_BTN1~8 by myself
        // See process_action() in quantum/action.c for details.
#ifndef MOUSEKEY_ENABLE
        case KC_MS_BTN1 ... KC_MS_BTN8:
            {
                extern void register_button(bool, enum mouse_buttons);
                register_button(record->event.pressed, MOUSE_BTN_MASK(keycode - KC_MS_BTN1));
                break;
            }
#endif

        case CPI_RST:
            if (record->event.pressed) {
                pointing_device_set_cpi(KEYBALL_CPI_DEFAULT);
            }
            break;
        case CPI_SAVE:
            if (record->event.pressed) {
                keyball_config_t c = { .cpi = cpi_value / 100 };
                eeconfig_update_kb(c.raw);
            }
            break;
        case CPI_I100:
            if (record->event.pressed) {
                add_cpi(100);
            }
            break;
        case CPI_D100:
            if (record->event.pressed) {
                add_cpi(-100);
            }
            break;
        case CPI_I1K:
            if (record->event.pressed) {
                add_cpi(1000);
            }
            break;
        case CPI_D1K:
            if (record->event.pressed) {
                add_cpi(-1000);
            }
            break;

        case SCRL_TO:
            if (record->event.pressed) {
                scroll_mode = !scroll_mode;
            }
            break;
        case SCRL_MO:
            scroll_mode = record->event.pressed;
            break;

        default:
            return true;
    }
    return false;
}

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    // store mouse report for OLED.
    last_mouse = pointing_device_task_user(mouse_report);
    return last_mouse;
}
