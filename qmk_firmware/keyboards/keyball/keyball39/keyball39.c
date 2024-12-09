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
-------------------------------------------------------------------
参考文献：
- リポジトリ：
  https://github.com/kamiichi99/keyball/tree/main/qmk_firmware/keyboards/keyball/keyball39/keymaps/kamidai
- keyballの販売ページ
  https://shirogane-lab.com/collections/all
コード表：
- 公式ファームウェアのキーコード：
  KBC_RST(0x5DA5): Keyball 設定のリセット
  KBC_SAVE(0x5DA6): 現在の Keyball 設定を EEPROM に保存します
  CPI_I100(0x5DA7): CPI を 100 増加させます(最大:12000)
  CPI_D100(0x5DA8): CPI を 100 減少させます(最小:100)
  CPI_I1K(0x5DA9): CPI を 1000 増加させます(最大:12000)
  CPI_D1K(0x5DAA): CPI を 1000 減少させます(最小:100)
  SCRL_TO(0x5DAB): タップごとにスクロールモードの ON/OFF を切り替えます
  SCRL_MO(0x5DAC): キーを押している間、スクロールモードになります
  SCRL_DVI(0x5DAD): スクロール除数を１つ上げます(max D7 = 1/128)← 最もスクロール遅い
  SCRL_DVD(0x5DAE): スクロール除数を１つ下げます(min D0 = 1/1)← 最もスクロール速い
- オリジナルのキーコード：
  KC_BACK_TO_LAYER0_BTN1(0x5DAF): レイヤー0に遷移できるBTN1
  KC_DOUBLE_CLICK_BTN1(0x5DB0): 1タップでダブルクリックできるBTN1
  KC_TRIPLE_CLICK_BTN1(0x5DB1): 1タップでトリプルクリックできるBTN1
*/

#include QMK_KEYBOARD_H

#include "lib/keyball/keyball.h"

//////////////////////////////////////////////////////////////////////////////

// clang-format off
matrix_row_t matrix_mask[MATRIX_ROWS] = {
    0b00011111,
    0b00011111,
    0b00011111,
    0b00111111,
    0b00011111,
    0b00011111,
    0b00011111,
    0b00111111,
};
// clang-format on

void keyball_on_adjust_layout(keyball_adjust_t v) {
#ifdef RGBLIGHT_ENABLE
    // adjust RGBLIGHT's clipping and effect ranges
    uint8_t lednum_this = keyball.this_have_ball ? 22 : 24;
    uint8_t lednum_that = !keyball.that_enable ? 0 : keyball.that_have_ball ? 22 : 24;
    rgblight_set_clipping_range(is_keyboard_left() ? 0 : lednum_that, lednum_this);
    rgblight_set_effect_range(0, lednum_this + lednum_that);
#endif
}
