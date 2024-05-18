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
    LCTL_T(KC_TAB)   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                        KC_Y     , KC_U     , KC_I     , KC_O     , KC_MINUS     , S(KC_MINUS)   ,
    KC_LSFT   , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                        KC_H     , KC_J     , KC_K     , KC_L     , KC_P  ,  KC_EQUAL ,
    KC_LALT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                                        KC_B     , KC_N     , KC_M,KC_COMM  , KC_DOT   , S(KC_EQUAL) ,
              KC_NO,KC_NO,LT(1, KC_SPC)     ,KC_LEFT_GUI,LT(3,KC_LNG2),                  KC_LNG1,MO(2), KC_NO,     KC_NO  , MO(3)
  ),

  [1] = LAYOUT_universal(
    _______ ,  S(KC_5)   , S(KC_3)    , S(KC_SLASH)   ,  KC_GRAVE   , S(KC_4)    ,                                         _______    , S(KC_LEFT_BRACKET)    , S(KC_RIGHT_BRACKET)    , S(KC_GRAVE)    , S(KC_MINUS)   , _______   ,
    _______ ,  S(KC_2) , S(KC_SEMICOLON)  , S(KC_1)   , KC_QUOTE   , S(KC_QUOTE)   ,                                         S(KC_6)  , S(KC_9)  , S(KC_0)    , S(KC_COMM)  , S(KC_DOT)  , _______   ,
    _______ ,  S(KC_7) , KC_SEMICOLON  , KC_BACKSLASH , KC_SLASH  , S(KC_8)  ,                                         S(KC_BACKSLASH)  , KC_LEFT_BRACKET  , KC_RIGHT_BRACKET  , KC_COMM  , KC_DOT  , _______  ,
                  _______  , _______ , _______  ,         _______  , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),

  [2] = LAYOUT_universal(
    _______  , _______   , _______  , _______  , _______  , _______  ,                                       _______  , KC_DEL  , KC_UP  , KC_BACKSPACE  ,_______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______ ,                                                      KC_F12  , KC_LEFT , KC_DOWN, KC_RIGHT , _______  , RGB_TOG  ,
    _______ , _______  , _______  , _______  , _______  , _______ ,                                                  KC_F2,KC_ENTER, KC_SPACE   ,KC_ESCAPE,_______,_______,
                  _______  , _______  , _______  ,        _______  , _______  ,                  _______   , _______  , _______       , _______  , _______
  ),

  [3] = LAYOUT_universal(
    _______  ,S(KC_QUOTE), KC_7     , KC_8    , KC_9     , S(KC_8)  ,                                        _______  , _______  , _______ , _______ , _______ , _______  ,
    _______  ,S(KC_SEMICOLON), KC_4     , KC_5    , KC_6     , KC_RIGHT_BRACKET  ,                         _______  , _______  , _______  , _______ , _______  , _______  ,
    _______  ,S(KC_MINUS), KC_1     , KC_2    , KC_3     ,S(KC_RIGHT_BRACKET),                            _______  , _______ , _______ , _______  , _______  , _______ ,
                  KC_0     , KC_DOT  , _______  ,         _______  , _______  ,                  _______  , _______  , _______       , _______  , _______
  ),

  [4] = LAYOUT_universal(
    _______  , _______   , _______  , _______  , _______  , _______  ,                                        _______  , _______  , _______ , _______ , _______ , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______ ,                                        _______  , KC_MS_BTN1  , KC_MS_BTN2  , _______ , _______  , _______  ,
    _______ , _______  , _______  , _______  , _______  , _______ ,                                        _______  , KC_MS_BTN4 , KC_MS_BTN5 , _______  , _______  , _______ ,
                  _______  , _______  , _______  ,        _______  , _______  ,                   _______  , _______  , _______       , _______  , _______
  ),
};
// clang-format on

// Customize keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    default:
      return true; // Process all other keycodes normally
  }
}

layer_state_t layer_state_set_user(layer_state_t state) {
      switch(get_highest_layer(remove_auto_mouse_layer(state, true))) {
        case 3:
            // Auto enable scroll mode when the highest layer is 3
            // remove_auto_mouse_target must be called to adjust state *before* setting enable
            state = remove_auto_mouse_layer(state, false);
            set_auto_mouse_enable(false);
            keyball_set_scroll_mode(true);
            break;
        default:
            set_auto_mouse_enable(true);
            keyball_set_scroll_mode(false);
            break;
    }
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
