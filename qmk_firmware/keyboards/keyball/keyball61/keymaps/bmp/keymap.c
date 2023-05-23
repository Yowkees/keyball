/* Copyright 2019 sekigon-gonnoc
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "bmp.h"
#include "bmp_custom_keycode.h"
#include "pointing_device.h"
#include "keycode_str_converter.h"
#include "lib/keyball/keyball.h"

report_mouse_t local_mouse_report = {};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    LOWER = KEYBALL_SAFE_RANGE,
    RAISE,
};

const key_string_map_t custom_keys_user = {
    .start_kc = KBC_RST,
    .end_kc = RAISE,
    .key_strings =
    "KBC_RST\0KBC_SAVE\0"
    "CPI_I100\0CPI_D100\0CPI_I1K\0CPI_D1K\0"
    "SCRL_TO\0SCRL_MO\0SCRL_DVI\0SCRL_DVD\0"
    "LOWER\0RAISE\0"
};

enum layers { _BASE, _LOWER, _RAISE, _ADJUST };

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {{{KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P, KC_Q, KC_R, KC_S}}};

uint32_t keymaps_len() { return sizeof(keymaps) / sizeof(uint16_t); }

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    bool continue_process = process_record_user_bmp(keycode, record);
    if (continue_process == false) {
        return false;
    }

    switch (keycode) {
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        default:
            break;
    }

    return true;
}

void pointing_device_init(void) {
    pointing_device_driver_init();
}

void pointing_device_task() {
    local_mouse_report = pointing_device_driver_get_report(local_mouse_report);
    pointing_device_set_report(local_mouse_report);
    pointing_device_send();
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
}
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}