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
  [0] = LAYOUT_universal(
    KC_Q     , KC_W     , KC_E     , KC_R     , KC_W     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , KC_K     , KC_L     , KC_MINS  ,
    KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  ,
    KC_LCTL  , LGUI_T(KC_TAB)  , KC_LALT  ,LSFT_T(KC_LNG2),LT(3,KC_SPC),LT(2,KC_LNG1),KC_BSPC,LT(1,KC_ENT),LSFT_T(KC_LNG2),KC_RALT,KC_RGUI, RSFT_T(KC_ESC)
  ),

  [1] = LAYOUT_universal(
    KC_AT    , KC_7    , KC_8    , KC_9    , KC_QUOT  ,                            KC_LCBR    ,   KC_EQL  , KC_TILD    , KC_PIPE    ,  KC_RCBR  ,
    KC_EXLM    , KC_4    , KC_5     , KC_6    , KC_DQUO  ,                           KC_LPRN, KC_PLUS  , KC_UNDS  , KC_SCLN     , KC_RPRN  ,
    S(KC_SLSH) , KC_1    , KC_2     , KC_3    , KC_EQL,                            KC_LBRC  , KC_ASTR   , KC_PERC  , KC_COLN  , KC_RBRC   ,
    KC_DLR  , KC_0   , S(KC_MINS)  , _______  , _______  , _______  ,      TO(2)    , TO(0)   , _______  , KC_RALT  , KC_RGUI  , KC_HASH
  ),

  [2] = LAYOUT_universal(
    KC_PSCR   , KC_F7     , KC_F8     , KC_F9     , KC_LSFT,                     KC_ESC  , SSNP_VRT  , SSNP_HOR  , SSNP_FRE  , KC_BSPC  ,
   KC_TAB , KC_F4     , KC_F5     , KC_F6     , KC_LCTL,                           SCRL_TO  , KC_BTN1  , KC_UP    , KC_BTN2  , KC_QUOT  ,
    KC_LSFT  , KC_F1     , KC_F2     , KC_F3     , KC_LGUI ,                           KC_HOME, KC_LEFT  , KC_DOWN  , KC_RGHT  , KC_END ,
    KC_LCTL   , KC_0     , KC_LALT   , KC_DEL   , KC_ENT   , KC_BSPC  ,      _______  , _______  , _______  , _______  , _______  , KC_ESC
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  ,                            _______  , _______  , SSNP_HOR , SSNP_VRT , SSNP_FRE ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , SCRL_DVI ,                            _______  , _______  , _______  , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , SCRL_DVD ,                            CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE ,
    QK_BOOT  , KBC_RST  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , KBC_RST  , QK_BOOT
  ),

  [4] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  ,                            _______  , _______  , SSNP_HOR , SSNP_VRT , SSNP_FRE ,
    RGB_MOD  , RGB_HUI  , KC_A  , RGB_VAI  , SCRL_DVI ,                            _______  , _______  , _______  , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , SCRL_DVD ,                            CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE ,
    QK_BOOT  , KBC_RST  , _______  , _______  , _______  , _______  ,      _______  , _______  , _______  , _______  , KBC_RST  , QK_BOOT
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    //auto enable scroll mode when the highest layer is 3
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

const uint16_t PROGMEM combo1[] = {LT(1,KC_ENT), LT(2,KC_LNG1), COMBO_END};
const uint16_t PROGMEM combo2[] = {KC_PIPE, KC_RCBR, COMBO_END};
combo_t key_combos[] = {
    COMBO(combo1, TT(4)),
    COMBO(combo2, KC_BSLS),
};
