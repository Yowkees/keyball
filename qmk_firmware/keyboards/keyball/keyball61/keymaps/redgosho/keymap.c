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
    KC_GRAVE , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                                  KC_6     , KC_7       , KC_8     , KC_9     , KC_0     , KC_MINS  ,
    KC_TAB   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                  KC_Y     , KC_U       , KC_I     , KC_O     , KC_P     , KC_EQUAL ,
    MO(1)    , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                  KC_H     , KC_J       , KC_K     , KC_L     , KC_SCLN  , KC_QUOTE ,
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     , KC_LNG2  ,              KC_LNG1, KC_N     , LT(3,KC_M) , KC_COMM  , KC_DOT   , KC_SLSH  , MO(3)  ,
    KC_LCTL  , KC_LGUI  , KC_LALT  , KC_SPC,LT(3,KC_SPC),LT(4,KC_LNG2),LT(2,KC_LNG1),         KC_BSPC ,LT(1,KC_ENT) , _______ , _______  , _______  , _______  , _______
  ),

  [1] = LAYOUT_universal(
    KC_ESC   , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                                  KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , KC_HOME  , KC_UP    , KC_END   , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , KC_LEFT  , KC_DOWN  , KC_RGHT  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,            _______  , _______  , _______  , KC_LBRC  , KC_RBRC  , KC_BSLS  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,            KC_DEL  , _______  , _______  , _______  , _______  , _______  , _______
  ),

  [2] = LAYOUT_universal(
    _______  , KC_F11   , KC_F12   , KC_F13   , KC_F14   , KC_F15   ,                                  KC_F16   , KC_F17   , KC_F18   , KC_F19   , KC_F20   , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , KC_BRID  , KC_BRIU  , KC_MPRV  , _______  ,            _______  , KC_MNXT  , KC_MPLY  , KC_KB_VOLUME_DOWN , KC_KB_VOLUME_UP , KC_KB_MUTE , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,            _______  , _______  , _______  , _______  , _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    _______  , KC_F21   , KC_F22   , KC_F23   , KC_F24   , _______  ,                                  _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , KBC_RST  , SCRL_TO  ,                                  _______  , _______  , CPI_D1K  , CPI_I1K  , _______  , _______  ,
    _______  , _______  , KBC_SAVE , _______  , _______  , _______  ,                                  _______  , _______  , CPI_D100 , CPI_I100 , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , EE_CLR  ,              EE_CLR  , _______  , _______  , SCRL_DVI , SCRL_DVD , _______ , _______  ,
    QK_BOOT  , _______  , _______  , _______  , _______  , _______  , _______  ,            _______  , _______  , _______  , _______  , _______  , _______  , QK_BOOT
  ),

  [4] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                  _______  , KC_BTN1  , KC_BTN2  , KC_BTN3  , _______  , _______  ,
    _______  , KC_UNDO  , KC_CUT   , KC_COPY  , KC_PASTE , _______  , _______  ,            _______  , _______  , _______  , KC_BTN4  , KC_BTN5  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,            _______  , _______  , _______  , _______  , _______  , _______  , _______
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t rgb_layer = biton32(state);
    uint8_t layer = get_highest_layer(remove_auto_mouse_layer(state, true));
    bool is_scroll_mode_layer = (layer == 3);

    // Set RGB LED color based on the active layer
    HSV hsv_color;
    switch (rgb_layer) {
      case 0: hsv_color = (HSV){ .h = 0, .s = 255, .v = 255 };     break;
      case 1: hsv_color = (HSV){ .h = 213, .s = 255, .v = 255 };   break;
      case 2: hsv_color = (HSV){ .h = 170, .s = 255, .v = 255 };   break;
      case 3: hsv_color = (HSV){ .h = 128, .s = 255, .v = 255 };   break;
      case 4: hsv_color = (HSV){ .h = 0, .s = 0, .v = 255 };       break;
      default: hsv_color = (HSV){ .h = 0, .s = 255, .v = 255 };    break;
    }
    rgblight_sethsv(hsv_color.h, hsv_color.s, hsv_color.v);

    // Set auto mouse and scroll mode based on the layer
    set_auto_mouse_enable(!is_scroll_mode_layer);
    keyball_set_scroll_mode(is_scroll_mode_layer);

    if (is_scroll_mode_layer) {
        state = remove_auto_mouse_layer(state, false);
    }
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_layerinfo();
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
}
#endif

void pointing_device_init_user(void) {
    // set_auto_mouse_layer(<mouse_layer>); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
}
