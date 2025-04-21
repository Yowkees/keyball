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
  KC_PSCR   , KC_F2     , KC_F3     , KC_C     , KC_V,                     KC_X  , SSNP_VRT  , SSNP_HOR  , SSNP_FRE  , KC_BSPC  ,
  KC_F4     , KC_F5     , KC_F6     , KC_TAB  , KC_LALT,                           SCRL_TO  , KC_BTN1  , KC_UP    , KC_BTN2  , TG(0) ,
  KC_F7     , KC_F8     , KC_F9     , KC_LSFT  , KC_LGUI ,                           KC_HOME, KC_LEFT  , KC_DOWN  , KC_RGHT  , KC_END ,
  KC_F10   , KC_F11     , KC_F12   , KC_BSPC   , KC_ENT   , KC_LCTL  ,      TG(2)  , TG(1)  , _______  , _______  , _______  , RSFT_T(KC_ESC)
  ),
  [1] = LAYOUT_universal(
    KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , RCTL_T(KC_K) , RWIN_T(KC_L)    , KC_MINS  ,
    KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  ,
    LCTL_T(KC_TAB), KC_LGUI, KC_LALT,KC_BSPC  , KC_ENT   ,KC_SPC,   LT(2,KC_LNG1)   , RSFT_T(KC_LNG2), _______, _______,_______, RSFT_T(KC_ESC)
  ),

  [2] = LAYOUT_universal(
    KC_1    , KC_2     , KC_3    , KC_LBRC   , S(KC_2)  ,                            S(KC_RBRC)    ,   KC_INT1  , S(KC_6)    , S(KC_INT3)    ,  S(KC_BSLS)  ,
    KC_4    , KC_5     , KC_6    , KC_EXLM   ,  S(KC_7)  ,                           S(KC_8), S(KC_SCLN)  , S(KC_INT1)  , KC_SCLN     , S(KC_9)  ,
    KC_7    , KC_8     , KC_9    , KC_DLR    ,  KC_EQL,                            KC_RBRC  , KC_DQUO   , KC_PERC  , KC_QUOT  , KC_BSLS   ,
    KC_0    , KC_HASH  , S(KC_EQL)  , _______  , TG(0)  , KC_SPC ,       _______   , TG(1)   , _______  , KC_RALT  , KC_RGUI  , S(KC_LBRC)
  ),


  [3] = LAYOUT_universal(
    RGB_TOG  , AML_TO   , AML_I50  , AML_D50  , _______  ,                            _______  , _______  , SSNP_HOR , SSNP_VRT , SSNP_FRE ,
    RGB_MOD  , RGB_HUI  , RGB_HUI  , RGB_VAI  , SCRL_DVI ,                            _______  , _______  , _______  , _______  , _______  ,
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

const uint16_t PROGMEM combo1[] = {LT(1,KC_LNG2), LT(2,KC_BSPC), COMBO_END};
const uint16_t PROGMEM combo2[] = {S(KC_INT3), S(KC_BSLS), COMBO_END};
combo_t key_combos[] = {
    COMBO(combo1, TT(3)),
    COMBO(combo2, KC_BSLS),
};
