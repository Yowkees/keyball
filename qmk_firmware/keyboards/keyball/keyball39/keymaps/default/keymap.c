/*
Copyright 2022 @Yowkees
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

#include "quantum.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  [0] = LAYOUT_universal(
    KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , KC_K     , KC_L     , KC_MINS  ,
    KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  ,
    KC_LCTL  , KC_LGUI  , KC_LALT  ,LSFT_T(KC_LNG2),LT(1,KC_SPC),LT(3,KC_LNG1),KC_BSPC,LT(2,KC_ENT),LSFT_T(KC_LNG2),KC_RALT,KC_RGUI, KC_RSFT
  ),

  [1] = LAYOUT_universal(
    KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_RBRC  ,                            KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   ,
    KC_F5    , KC_EXLM  , S(KC_6)  ,S(KC_INT3), S(KC_8)  ,                           S(KC_INT1), KC_BTN1  , KC_PGUP  , KC_BTN2  , KC_SCLN  ,
    S(KC_EQL),S(KC_LBRC),S(KC_7)   , S(KC_2)  ,S(KC_RBRC),                            KC_LBRC  , KC_DLR   , KC_PGDN  , KC_BTN3  , KC_F11   ,
    KC_INT1  , KC_EQL   , S(KC_3)  , _______  , _______  , _______  ,      TO(2)    , TO(0)    , _______  , KC_RALT  , KC_RGUI  , KC_F12
  ),

  [2] = LAYOUT_universal(
    KC_TAB   , KC_7     , KC_8     , KC_9     , KC_MINS  ,                            KC_NUHS  , _______  , KC_BTN3  , _______  , KC_BSPC  ,
   S(KC_QUOT), KC_4     , KC_5     , KC_6     ,S(KC_SCLN),                            S(KC_9)  , KC_BTN1  , KC_UP    , KC_BTN2  , KC_QUOT  ,
    KC_SLSH  , KC_1     , KC_2     , KC_3     ,S(KC_MINS),                           S(KC_NUHS), KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  ,
    KC_ESC   , KC_0     , KC_DOT   , KC_DEL   , KC_ENT   , KC_BSPC  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  ,                            _______  , _______  , SSNP_HOR , SSNP_VRT , SSNP_FRE ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , SCRL_DVI ,                            _______  , _______  , _______  , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , SCRL_DVD ,                            CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE ,
    QK_BOOT  , KBC_RST  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , KBC_RST  , QK_BOOT
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif

// ================================================
// 2025-10-06追加_スクロール、トラックボール低速
// ================================================
#define HOLD_MS 150

static bool init_done = false;
static uint8_t base_scroll_div;  // 1..7
static uint8_t base_cpi;         // 100cpi単位

static bool v_active = false;
static bool h_active = false;

static uint16_t q_t = 0, w_t = 0;
static bool q_down = false, w_down = false;

// ---- 追加: E/R 用 ----
static uint16_t e_t = 0, r_t = 0;
static bool e_down = false, r_down = false;
static bool e_used = false;   // Eが“加速用途”に使われたか
static bool r_used = false;   // Rが“低速用途”に使われたか

static inline bool held_long(uint16_t t0) { return timer_elapsed(t0) > HOLD_MS; }

static inline void ensure_init(void){
    if (init_done) return;
    base_scroll_div = keyball_get_scroll_div();
    if (base_scroll_div < 1) base_scroll_div = 1;
    if (base_scroll_div > 7) base_scroll_div = 7;

    base_cpi = keyball_get_cpi();   // 例: 12 = 1200cpi
    init_done = true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    ensure_init();

    switch (keycode) {
        // --- Q: 縦スクロール（長押し）/ 'q'（タップ）
        case KC_Q:
            if (record->event.pressed) {
                q_down = true; q_t = timer_read();
            } else {
                q_down = false;
                if (v_active) {
                    v_active = false;
                    if (get_highest_layer(layer_state) != 3) keyball_set_scroll_mode(false);
                } else {
                    q_t = 0; tap_code16(KC_Q);
                }
            }
            return false;

        // --- W: 横スクロール（長押し）/ 'w'（タップ）
        case KC_W:
            if (record->event.pressed) {
                w_down = true; w_t = timer_read();
            } else {
                w_down = false;
                if (h_active) {
                    h_active = false;
                    if (get_highest_layer(layer_state) != 3) keyball_set_scroll_mode(false);
                } else {
                    w_t = 0; tap_code16(KC_W);
                }
            }
            return false;

        // --- E: スクロール中だけ加速（ホールド）/ 'e'（タップ）
        case KC_E:
            if (record->event.pressed) {
                e_down = true; e_t = timer_read(); e_used = false;
                // すでにスクロール中なら即加速・“使った”扱い
                if (v_active || h_active) {
                    uint8_t faster = base_scroll_div > 1 ? (base_scroll_div - 1) : 1;
                    keyball_set_scroll_div(faster);
                    e_used = true;
                }
            } else {
                // Eを離した
                if (e_used) {
                    // 加速に使っていた → 通常速度へ戻す
                    keyball_set_scroll_div(base_scroll_div);
                } else {
                    // タップとみなす（ホールド未成立＆スクロール未使用）
                    if (!held_long(e_t)) tap_code16(KC_E);
                }
                e_down = false; e_t = 0; e_used = false;
            }
            return false;

        // --- R: 長押しでCPI低下（低速）/ 'r'（タップ）
        case KC_R:
            if (record->event.pressed) {
                r_down = true; r_t = timer_read(); r_used = false;
                // 低速は“長押し成立後”に適用（matrix_scan_userで実行）
            } else {
                // Rを離した
                if (r_used) {
                    // 低速にしていた → 元のCPIに戻す
                    keyball_set_cpi(base_cpi);
                } else {
                    // タップ扱い（低速を有効化していない）
                    if (!held_long(r_t)) tap_code16(KC_R);
                }
                r_down = false; r_t = 0; r_used = false;
            }
            return false;
    }
    return true;
}

void matrix_scan_user(void) {
    ensure_init();

    // 縦スクロール開始（Q長押し）
    if (!v_active && q_down && q_t && held_long(q_t)) {
#if KEYBALL_SCROLLSNAP_ENABLE == 2
        keyball_set_scrollsnap_mode(KEYBALL_SCROLLSNAP_MODE_VERTICAL);
#endif
        keyball_set_scroll_mode(true);
        // Eが押下済みで未使用なら、ここで初めて“加速に使った”扱いにして反映
        if (e_down && !e_used) {
            uint8_t faster = base_scroll_div > 1 ? (base_scroll_div - 1) : 1;
            keyball_set_scroll_div(faster);
            e_used = true;
        } else {
            keyball_set_scroll_div(base_scroll_div);
        }
        v_active = true;
        q_t = 0;
    }

    // 横スクロール開始（W長押し）
    if (!h_active && w_down && w_t && held_long(w_t)) {
#if KEYBALL_SCROLLSNAP_ENABLE == 2
        keyball_set_scrollsnap_mode(KEYBALL_SCROLLSNAP_MODE_HORIZONTAL);
#endif
        keyball_set_scroll_mode(true);
        if (e_down && !e_used) {
            uint8_t faster = base_scroll_div > 1 ? (base_scroll_div - 1) : 1;
            keyball_set_scroll_div(faster);
            e_used = true;
        } else {
            keyball_set_scroll_div(base_scroll_div);
        }
        h_active = true;
        w_t = 0;
    }

    // R 長押し成立で低CPIを適用（押してすぐは適用しない → タップ入力が生きる）
    if (r_down && !r_used && held_long(r_t)) {
        uint8_t slow = base_cpi > 4 ? (uint8_t)(base_cpi - 2) : base_cpi; // 200cpiダウン
        keyball_set_cpi(slow);
        r_used = true;
    }
}
