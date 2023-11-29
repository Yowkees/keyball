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
  [0] = LAYOUT_universal(
    KC_GRAVE , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                                   KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_MINS  ,
    KC_EQUAL , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                   KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_BSLS  ,
    KC_TAB   , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                   KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , KC_QUOT  ,
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     , KC_LBRC  ,              KC_RBRC , KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_RSFT  ,
    KC_ESC   , _______  , _______  , KC_LALT  , KC_BSPC  , KC_LCTL  , KC_LGUI  ,              KC_ENT  , KC_SPC   , KC_NO    , KC_NO    , KC_NO    , _______  , MO(1)
  ),

  // mouse layer
  [1] = LAYOUT_universal(
    KC_NO    , KC_NO         , KC_NO         , KC_NO         , KC_NO         , KC_NO         ,                                   KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    ,
    KC_NO    , _______       , LCTL(KC_UP)   , LAG(KC_F)     , LCTL(KC_DOWN) , KC_NO         ,                                   _______  , KC_BTN1  , KC_UP    , KC_BTN2  , KC_NO    , SCRL_MO  ,
    KC_NO    , LCTL(KC_LEFT) , LAG(KC_LEFT)  , KC_NO         , LAG(KC_RGHT)  , LCTL(KC_RGHT) ,                                   KC_NO    , KC_LEFT  , KC_DOWN  , KC_RGHT  , KC_NO    , KC_NO    ,
    KC_NO    , KC_NO         , KC_NO         , _______       , _______       , KC_NO         , KC_NO    ,             KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    , KC_NO    ,
    KC_NO    , KC_NO         , KC_NO         , _______       , _______       , _______       , _______  ,             _______  , _______  , KC_NO    , KC_NO    , KC_NO    , KC_NO    , _______
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

#ifdef OLED_ENABLE

#include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif

#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
void pointing_device_init_user(void) {
  set_auto_mouse_enable(true);
}
#endif
