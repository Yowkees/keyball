/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)
Copyright 2023 kamidai <@d_kamiichi>

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

#include "features/my_functions.h"
#include "features/swipe_gesture.h"
#include "features/auto_click_layer.h"
#include "features/my_macro_keys.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  [0] = LAYOUT_universal(
SFT_T(KC_TAB), KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , SFT_T(KC_P),
   LT(2,KC_A), KC_S     , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , KC_K     , KC_L     , LT(2,KC_SCOLON),
    KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLASH  ,
    KC_LALT  ,KC_F5, LT(1,KC_Q) , KC_SPACE ,CTL_T(KC_DEL), KC_ESC  ,      KC_BSPC  , KC_ENT   , _______  , _______  , _______  , LT(3,KC_ESC)
  ),

  [1] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                           G(KC_LBRC), _______  , G(KC_1)  , G(KC_2)  , _______  ,
    _______  ,C(KC_LEFT), KC_LEFT  , KC_RIGHT,C(KC_RIGHT),                           G(KC_RBRC), KC_DOWN  , KC_UP    , G(KC_V)  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            G(KC_Z)  , G(KC_C)  , G(KC_X)  , G(KC_A)  ,SGUI(KC_Z),
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  [2] = LAYOUT_universal(
    _______  , _______  , S(KC_1)  ,S(KC_SLSH), _______  ,                            KC_NUM   , KC_7     , KC_8     , KC_9     , KC_MINUS ,
    KC_LBRC  , S(KC_9)  , S(KC_0)  , KC_RBRC  , KC_QUOTE ,                            KC_COMMA , KC_4     , KC_5     , KC_6     , KC_EQUAL ,
    _______  , _______  , _______  , _______  , KC_SCOLON,                            KC_DOT	 , KC_1     , KC_2     , KC_3     ,KC_BSLS  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______ ,  KC_0     , _______  , _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , RGB_MOD  , RGB_RMOD , _______  , _______  ,                            RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN ,
    SCRL_DVD , SCRL_DVI , CPI_D100 , CPI_I100 , _______  ,                            RGB_M_K  , RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    RESET    , _______  , _______  , _______  , _______  , _______  ,      _______ ,  _______  , _______  , _______  , _______  , _______
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
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  ,KC_MY_BTN1, _______  ,KC_MY_BTN2, _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______ ,  _______  , _______  , _______  , _______  , _______  
  )
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state)
{
  // レイヤーが1または3の場合、スクロールモードが有効になる
  // keyball_set_scroll_mode(get_highest_layer(state) == 3);
  keyball_set_scroll_mode(get_highest_layer(state) == 1 || get_highest_layer(state) == 3);

  // レイヤーとLEDを連動させる
  uint8_t layer = biton32(state);
  switch (layer)
  {
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

void oledkit_render_info_user(void)
{
  keyball_oled_render_keyinfo();
  keyball_oled_render_ballinfo();

  // <Layer>を表示する
  oled_write_P(PSTR("Layer:"), false);
  oled_write(get_u8_str(get_highest_layer(layer_state), ' '), false);

  // <マウス移動量 / クリックレイヤーしきい値>を表示
  // oled_write_P(PSTR(" MV:"), false);
  // oled_write(get_u8_str(mouse_movement, ' '), false);
  // oled_write_P(PSTR("/"), false);
  // oled_write(get_u8_str(to_clickable_movement, ' '), false);

  // <state>を表示
  switch (state)
  {
  case NONE:
    oled_write_ln_P(PSTR("  NONE"), false);
    break;
  case CLICKABLE:
    oled_write_ln_P(PSTR("  CLICKABLE"), false);
    break;
  case WAITING:
    oled_write_ln_P(PSTR("  WAITING"), false);
    break;
  case CLICKING:
    oled_write_ln_P(PSTR("  CLICKING"), false);
    break;
  case SWIPE:
    oled_write_ln_P(PSTR("  SWIPE"), false);
    break;
  case SWIPING:
    oled_write_ln_P(PSTR("  SWIPING"), false);
    break;
  }
}
#endif
