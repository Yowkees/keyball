/*
 * Copyright 2022 @Yowkees
 * Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)
 * Copyright 2023 kamidai (@d_kamiichi)
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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------
 *
 * 参考文献：
 * - リポジトリ：
 *   https://github.com/kamiichi99/keyball/tree/main/qmk_firmware/keyboards/keyball/keyball39/keymaps/kamidai
 *
 * - keyballの販売ページ
 *   https://shirogane-lab.com/collections/all
 *
 * コード表：
 * - 公式ファームウェアのキーコード：
 *   KBC_RST(0x5DA5): Keyball 設定のリセット
 *   KBC_SAVE(0x5DA6): 現在の Keyball 設定を EEPROM に保存します
 *   CPI_I100(0x5DA7): CPI を 100 増加させます(最大:12000)
 *   CPI_D100(0x5DA8): CPI を 100 減少させます(最小:100)
 *   CPI_I1K(0x5DA9): CPI を 1000 増加させます(最大:12000)
 *   CPI_D1K(0x5DAA): CPI を 1000 減少させます(最小:100)
 *   SCRL_TO(0x5DAB): タップごとにスクロールモードの ON/OFF を切り替えます
 *   SCRL_MO(0x5DAC): キーを押している間、スクロールモードになります
 *   SCRL_DVI(0x5DAD): スクロール除数を１つ上げます(max D7 = 1/128)← 最もスクロール遅い
 *   SCRL_DVD(0x5DAE): スクロール除数を１つ下げます(min D0 = 1/1)← 最もスクロール速い
 *
 * - オリジナルのキーコード：
 *   KC_BACK_TO_LAYER0_BTN1(0x5DAF): レイヤー0に遷移できるBTN1
 *   KC_DOUBLE_CLICK_BTN1(0x5DB0): 1タップでダブルクリックできるBTN1
 *   KC_TRIPLE_CLICK_BTN1(0x5DB1): 1タップでトリプルクリックできるBTN1
 */

#include QMK_KEYBOARD_H
#include "quantum.h"

#include "utils/functions.h"
#include "features/swipe_gesture.h"
#include "features/auto_click_layer.h"
// #include "features/back_to_layer0_btn1.h"
// #include "features/one_tap_multi_click.h"
#include "features/macro_keys.h"

// 容量オーバーのため不使用（VIAをOFFにすれば、使用可能）
// #include "features/overrides.h"
#include "features/combo.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  [0] = LAYOUT_universal(
    KC_TAB   , KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , KC_K     , KC_L     , KC_F5    ,
    KC_Z     , KC_X     , KC_C     ,LT(2,KC_V),SFT_T(KC_B),                         SFT_T(KC_N), KC_M     , KC_COMMA , KC_DOT   , KC_SLASH ,
    LT(1,KC_LANG2),ALT_T(KC_F13),LT(3,KC_ESC),CMD_T(KC_SPACE),CTL_T(KC_Y),LT(5,KC_Q),    KC_BSPC,CMD_T(KC_ENT),_______,_______,_______,LT(1,KC_LANG1)
  ),

  [1] = LAYOUT_universal(
    _______  ,HYPR(KC_4),SGUI(KC_4),SGUI(KC_3),SGUI(KC_5),                           G(KC_LBRC),G(KC_RBRC), KC_UP    , KC_RIGHT , KC_TAB   ,
    _______  ,S(KC_LEFT), C(KC_J)  , _______  , _______  ,                            KC_LEFT  , KC_DOWN  , C(KC_K)  ,S(KC_RIGHT), C(KC_Y) ,
    C(KC_LEFT), _______ , _______  , _______  ,SFT_T_G_KC_A,                          G(KC_Z)  , G(KC_C)  , G(KC_X)  , G(KC_V)  ,G(KC_SLASH),
    _______ , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  [2] = LAYOUT_universal(
    _______  , KC_7     , KC_8     , KC_9     , _______  ,                            S(KC_4)  , KC_7     , KC_8     , KC_9     ,KC_BSLASH ,
    KC_0     , KC_4     , KC_5     , KC_6     , _______  ,                            _______  , KC_4     , KC_5     , KC_6     , S(KC_5)  ,
    _______  , KC_1     , KC_2     , KC_3     , _______  ,                    SFT_T(KC_NUMLOCK), KC_1     , KC_2     , KC_3     , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , KC_0     , _______  , _______  , _______  , _______  
  ),

  [3] = LAYOUT_universal(
    _______ , S(KC_2)   , S(KC_3)  , KC_QUOTE ,S(KC_QUOTE),                           _______  ,S(KC_RBRC), KC_RBRC  ,S(KC_EQUAL),S(KC_8)  ,
    S(KC_GRAVE),S(KC_MINUS),S(KC_COMMA),S(KC_7),S(KC_BSLASH),                        S(KC_LBRC), KC_LBRC  , S(KC_0)  , KC_MINUS , KC_EQUAL ,
    A(KC_BSLASH),S(KC_6), _______  ,S(KC_DOT) ,SFT_T_S_KC_SCOLON,               SFT_T(KC_GRAVE), S(KC_9)  , S(KC_1)  ,S(KC_SLASH),KC_SCOLON,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),

  [4] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______  
  ),

  [5] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                            _______  , SCRL_DVI , CPI_I100 , _______  , RGB_TOG  ,
    _______  , _______  , _______  , _______  , _______  ,                            SCRL_DVD , CPI_D100 , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,        RESET  , KBC_RST  , _______  , _______  , _______  , _______  
  ),

  [6] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    KC_LALT  , KC_LSFT  , _______  ,KC_MS_BTN1, _______ ,                            _______  ,KC_MS_BTN1,KC_MS_BTN3,KC_MS_BTN2, _______  ,
    _______  , _______  , _______  , _______  , _______  ,                            _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , _______  , _______  
  )
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
  // レイヤーが1または3の場合、スクロールモードが有効になる
  keyball_set_scroll_mode(get_highest_layer(state) == 1 || get_highest_layer(state) == 3);
  // keyball_set_scroll_mode(get_highest_layer(state) == 1);

  // レイヤーとLEDを連動させる
  switch (get_highest_layer(state)) {
    case click_layer:
      rgblight_sethsv(HSV_WHITE);
      break;
    case 1:
      rgblight_sethsv(HSV_RED);
      break;
    case 2:
      rgblight_sethsv(HSV_YELLOW);
      break;
    case 3:
      rgblight_sethsv(HSV_GREEN);
      break;

    default:
      rgblight_sethsv(HSV_OFF);
  }

  return state;
}

#ifdef OLED_ENABLE

#include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
  // デバッグ用に変数を表示する
  // oled_write_P(PSTR("Debug:"), false);
  // oled_write(get_u8_str(xxx, ' '), false);

  keyball_oled_render_keyinfo();   // キー情報を表示
  keyball_oled_render_ballinfo();  // トラックボール情報を表示

  // <Layer>を表示する
  oled_write_P(PSTR("Layer:"), false);
  oled_write(get_u8_str(get_highest_layer(layer_state), ' '), false);

  // <マウス移動量 / クリックレイヤーしきい値>を表示
  // oled_write_P(PSTR(" MV:"), false);
  // oled_write(get_u8_str(mouse_movement, ' '), false);
  // oled_write_P(PSTR("/"), false);
  // oled_write(get_u8_str(to_clickable_movement, ' '), false);

  // <state>を表示
  switch (state) {
    case WAITING:
      oled_write_ln_P(PSTR("  WAITING"), false);
      break;
    case CLICKABLE:
      oled_write_ln_P(PSTR("  CLICKABLE"), false);
      break;
    case CLICKING:
      oled_write_ln_P(PSTR("  CLICKING"), false);
      break;
    case CLICKED:
      oled_write_ln_P(PSTR("  CLICKED"), false);
      break;
    case SWIPE:
      oled_write_ln_P(PSTR("  SWIPE"), false);
      break;
    case SWIPING:
      oled_write_ln_P(PSTR("  SWIPING"), false);
      break;
    case NONE:
      oled_write_ln_P(PSTR("  NONE"), false);
      break;
  }
}
#endif
