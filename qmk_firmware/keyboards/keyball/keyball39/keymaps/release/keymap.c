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

// コード表
// 【KBC_RST: 0x5DA5】Keyball 設定のリセット
// 【KBC_SAVE: 0x5DA6】現在の Keyball 設定を EEPROM に保存します
// 【CPI_I100: 0x5DA7】CPI を 100 増加させます(最大:12000)
// 【CPI_D100: 0x5DA8】CPI を 100 減少させます(最小:100)
// 【CPI_I1K: 0x5DA9】CPI を 1000 増加させます(最大:12000)
// 【CPI_D1K: 0x5DAA】CPI を 1000 減少させます(最小:100)
// 【SCRL_TO: 0x5DAB】タップごとにスクロールモードの ON/OFF を切り替えます
// 【SCRL_MO: 0x5DAC】キーを押している間、スクロールモードになります
// 【SCRL_DVI: 0x5DAD】スクロール除数を１つ上げます(max D7 = 1/128)← 最もスクロール遅い
// 【SCRL_DVD: 0x5DAE】スクロール除数を１つ下げます(min D0 = 1/1)← 最もスクロール速い
// https://github.com/kamiichi99/keyball/tree/main/qmk_firmware/keyboards/keyball/keyball39/keymaps/kamidai
// https://shirogane-lab.com/collections/all

#include QMK_KEYBOARD_H
#include "quantum.h"

enum custom_keycodes {
  KC_MY_BTN0 = KEYBALL_SAFE_RANGE,  // Remap上では 0x5DAF（レイヤー0に遷移できるBTN1）
  KC_MY_BTN1,                       // Remap上では 0x5DB0
  KC_MY_BTN2,                       // Remap上では 0x5DB1
  KC_MY_BTN3,                       // Remap上では 0x5DB2
  KC_GESTURE1,                      // Remap上では 0x5DB3（ジェスチャーボタン1）
  KC_GESTURE2,                      // Remap上では 0x5DB4（ジェスチャーボタン2）
  KC_GESTURE3,                      // Remap上では 0x5DB5（ジェスチャーボタン3）
};
#include "features/functions.h"
#include "features/swipe_gesture.h"
#include "features/auto_click_layer.h"
#include "features/macro_keys.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  [0] = LAYOUT_universal(
    KC_TAB   , KC_A     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    KC_Z     , KC_S     , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , KC_K     , KC_L     , KC_MINUS ,
    KC_V     , KC_X     , KC_C     ,LT(2,KC_W),LT(3,KC_B),                            KC_N     , KC_M     , KC_COMMA , KC_DOT   , KC_SLASH ,
    LSFT_T(KC_LANG2),KC_LALT,LT(1,KC_ESC),LCMD_T(KC_SPACE),LCTL_T(KC_F13),KC_Q,       KC_BSPC, KC_ENT,_______,_______,_______, LT(1,KC_LANG1)
  ),

  [1] = LAYOUT_universal(
    _______  , G(KC_A)  , G(KC_F)  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , KC_LEFT  , KC_RIGHT , KC_SPACE ,                            G(KC_G)  , KC_DOWN  , KC_UP    , G(KC_V)  , _______  ,
    _______  , _______  ,C(KC_LEFT), _______ ,C(KC_RIGHT),                            G(KC_Z)  , G(KC_C)  , G(KC_X)  , _______  , G(KC_SLASH),
    _______, _______, _______, _______, _______, _______ ,                            _______  , _______  ,_______,_______,_______, _______
  ),

  [2] = LAYOUT_universal(
    _______  , _______  , _______  , KC_COMMA , KC_PDOT  ,                            KC_ESC   , KC_7     , KC_8     , KC_9     , KC_NUMLOCK,
    _______  , _______  , KC_LEFT  , KC_RIGHT , KC_SPACE ,                            KC_PSLS  , KC_4     , KC_5     , KC_6     , KC_PPLS  ,
    _______  , _______  , _______  , _______  , _______  ,                            KC_PMNS  , KC_1     , KC_2     , KC_3     , KC_PAST  ,
    _______, _______, _______, _______, _______, _______ ,                            _______  , KC_0     ,_______,_______,_______, _______
  ),

  [3] = LAYOUT_universal(
    KC_GRAVE , S(KC_2)  , S(KC_3)  , S(KC_4)  , S(KC_5)  ,                            S(KC_6)  , S(KC_7)  , S(KC_9)  , S(KC_0)  , S(KC_8)  ,
    _______  , _______  , KC_LEFT  , KC_RIGHT , KC_SPACE ,                            S(KC_1)  , KC_QUOTE , KC_LBRC  , KC_RBRC  , KC_EQUAL ,
    CPI_I100 , CPI_D100 , SCRL_DVI , SCRL_DVD , _______  ,                            KC_SCLN  , _______  , _______  , _______  , KC_BSLASH ,
    _______, _______, _______, _______, RGB_TOG , RESET  ,                            _______  , _______  ,_______,_______,_______, _______
  ),

  [4] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______ ,  _______  , _______  , _______  , _______  , _______  
  ),

  [5] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______ ,  _______  , _______  , _______  , _______  , _______  
  ),

  [6] = LAYOUT_universal(
    _______  ,KC_GESTURE1,KC_GESTURE2,KC_GESTURE3,_______,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  ,KC_MY_BTN1,KC_MY_BTN3,KC_MY_BTN2, _______  ,
    _______  , _______  , _______  ,KC_MY_BTN0,KC_MY_BTN0,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______ ,  _______  , _______  , _______  , _______  , _______  
  )
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
  // レイヤーが1または3の場合、スクロールモードが有効になる
  // keyball_set_scroll_mode(get_highest_layer(state) == 3);
  keyball_set_scroll_mode(get_highest_layer(state) == 1 || get_highest_layer(state) == 3);

  // レイヤーとLEDを連動させる
  uint8_t layer = biton32(state);
  switch (layer) {
    case 6:
      rgblight_sethsv(HSV_WHITE);
      break;

    default:
      rgblight_sethsv(HSV_OFF);
  }

  return state;
}

#ifdef OLED_ENABLE

#include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
  keyball_oled_render_keyinfo();
  keyball_oled_render_ballinfo();

  oled_write_P(PSTR("Layer:"), false);
  oled_write(get_u8_str(get_highest_layer(layer_state), ' '), false);
}
#endif
