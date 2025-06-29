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
  // keymap for default (VIA)
/*
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
*/
};
// clang-format on

#ifdef RGBLIGHT_ENABLE
bool cw_active = false;  // Caps Word用フラグ

void caps_word_set_user(bool active) {
    if (active) {  // Caps Wordが有効な場合
        rgblight_sethsv(HSV_RED);
        cw_active = true;
    } else {
        if (layer_state_is(6)) {
            rgblight_sethsv(HSV_GREEN);
        } else if (layer_state_is(5)) {
            rgblight_sethsv(HSV_BLUE);
        } else {
            rgblight_sethsv(HSV_OFF); // それ以外の場合、LEDを消灯
        }
        cw_active = false;
    }
}
#endif // RGBLIGHT_ENABLE

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);

#ifdef RGBLIGHT_ENABLE
    // レイヤーとLEDを連動させる
    switch (get_highest_layer(state)) {
        case 5:
            rgblight_sethsv(HSV_BLUE);
            break;
        case 6:
            rgblight_sethsv(HSV_GREEN);
            break;
        default:
            if (cw_active) {
                rgblight_sethsv(HSV_RED); // レイヤー5,6以外かつCaps Wordが有効な場合
            } else {
                rgblight_sethsv(HSV_OFF);
            }
    }
#endif // RGBLIGHT_ENABLE
    
// AML保持用
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    keyball_handle_auto_mouse_layer_change(state);
#endif

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

#ifdef HOLD_ON_OTHER_KEY_PRESS_PER_KEY
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_GRV):
        case LSFT_T(KC_SPC):
        case C_S_T(KC_MINS):
        case LT(1, KC_ENT):
        case LT(2, KC_TAB):
        case LT(3, KC_DOT):
        case LT(4, KC_ESC):
        case LSFT_T(KC_F10):
            // Immediately select the hold action when another key is pressed
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}
#endif // HOLD_ON_OTHER_KEY_PRESS_PER_KEY

#ifdef COMBO_ENABLE
enum combo_events {
  PARENTHESES,
  SQUARE_BRACKETS,
  CURLY_BRACKETS,
  PASTE_VALUE,
  CMB_ALTTAB,
  COMBO_COUNT  // Comboの数を自動計算
};

const uint16_t PROGMEM paren_combo[] = {KC_G, KC_H, COMBO_END};
const uint16_t PROGMEM sqbra_combo[] = {KC_T, KC_Y, COMBO_END};
const uint16_t PROGMEM cubra_combo[] = {KC_B, KC_N, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM combo_alttab[] = {KC_D, KC_F, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [PARENTHESES] = COMBO_ACTION(paren_combo),
  [SQUARE_BRACKETS] = COMBO_ACTION(sqbra_combo),
  [CURLY_BRACKETS] = COMBO_ACTION(cubra_combo),
  [PASTE_VALUE] = COMBO_ACTION(paste_combo),
  [CMB_ALTTAB] = COMBO(combo_alttab, KC_NO), // KC_NO to leave processing for process_combo_event
};
// COMBO_ACTION(x) is same as COMBO(x, KC_NO)

// Comboの状態管理
static bool combo_key_press_active[COMBO_COUNT] = { false };

void process_combo_event(uint16_t combo_index, bool pressed) {
  combo_key_press_active[combo_index] = pressed;  // Comboが押されている間はTRUE、離すとFALSE
  
  switch(combo_index) {
    case PARENTHESES:
      if (pressed) {
        tap_code16(S(KC_8));
        tap_code16(S(KC_9));
      }
      break;
    case SQUARE_BRACKETS:
      if (pressed) {
        tap_code(KC_RBRC);
        tap_code(KC_BSLS);
      }
      break;
    case CURLY_BRACKETS:
      if (pressed) {
        tap_code16(S(KC_RBRC));
        tap_code16(S(KC_BSLS));
      }
      break;
    case PASTE_VALUE:
      if (pressed) {
        tap_code16(C(S(KC_V)));
      }
      break;
    case CMB_ALTTAB:
      if (pressed) {
        register_mods(MOD_LALT);
        tap_code(KC_TAB);
      } else {
        unregister_mods(MOD_LALT);
      }
      break;    
  }
}

bool process_combo_key_repress(uint16_t combo_index, combo_t *combo, uint8_t row, uint16_t keycode, keyrecord_t *record) {
    if (!combo_key_press_active[combo_index]) {  // Comboが発動していなければ何もしない
        return false;
    }

    if (record->event.pressed) {
        if (combo_index == CMB_ALTTAB) {  
            if (keycode == KC_S) {
                tap_code16(S(KC_TAB)); // Shift + Tabを送信
                return true;
            } else if (keycode == KC_F) {
                tap_code(KC_TAB); // Tabを送信
                return true;
            }
        }
    }
    return false;
}
#endif  // COMBO_ENABLE

//////////////////////////////
/// カスタムキーコード。ここから ///
//////////////////////////////
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // CMB_ALTTAB用
#ifdef COMBO_ENABLE
        case KC_S:
        case KC_F:
            if (record->event.pressed) {
                // ComboのKey Repress処理
                for (uint16_t i = 0; i < COMBO_COUNT; i++) {
                    if (process_combo_key_repress(i, &key_combos[i], record->event.key.row, keycode, record)) {
                        return false; // Comboが処理された場合、通常のキー入力をキャンセル
                    }
                }
            }
            return true;  // Combo以外であれば通常のキー入力を行う
#endif // COMBO_ENABLE
    }
}
//////////////////////////////
/// カスタムキーコード。ここまで ///
//////////////////////////////
