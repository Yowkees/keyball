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
    KC_Q           , KC_W    , KC_E          , KC_R           , KC_T         ,                                         KC_Y , KC_U       , KC_I    , KC_O    , KC_P         ,
    KC_A           , KC_S    , KC_D          , CTL_T(KC_F)    , KC_G         ,                                         KC_H , KC_J       , KC_K    , KC_L    , KC_MINS      ,
    SFT_T(KC_Z)    , KC_X    , KC_C          , KC_V           , KC_B         ,                                         KC_N , KC_M       , MS_BTN1 , MS_BTN2 , LT(3,KC_TAB) ,
    SFT_T(KC_COMM) , KC_LCTL , ALT_T(KC_ESC) , CMD_T(KC_LNG1) , LT(1,KC_SPC) , LT(2,KC_LNG1) , LT(1,KC_BSPC) , LT(2,KC_ENT) , XXXXXXX    , XXXXXXX , XXXXXXX , KC_DOT
  ),

  [1] = LAYOUT_universal(
    KC_1           , KC_2    , KC_3          , KC_4           , KC_5         ,                                         KC_6 , KC_7       , KC_8    , KC_9    , KC_0         ,
    XXXXXXX        , XXXXXXX , XXXXXXX       , XXXXXXX        , XXXXXXX      ,                                      XXXXXXX , XXXXXXX    , XXXXXXX , XXXXXXX , XXXXXXX      ,
    KC_F1          , KC_F2   , KC_F3         , KC_F4          , KC_F5        ,                                        KC_F6 , KC_F7      , KC_F8   , KC_F9   , KC_F10       ,
    XXXXXXX        , XXXXXXX , XXXXXXX       , XXXXXXX        , _______      , _______       , _______ ,            _______ , XXXXXXX    , XXXXXXX , XXXXXXX , XXXXXXX
  ),

  [2] = LAYOUT_universal(
    XXXXXXX        , KC_HASH , KC_DLR        , KC_CIRC        , KC_TILD      ,                                      KC_SCLN , KC_COLN    , KC_LBRC  , KC_RBRC  , KC_BSPC    ,
    KC_PERC        , KC_ASTR , KC_SLSH       , KC_PLUS        , KC_EQL       ,                                      KC_QUOT , KC_DQUO    , KC_LPRN  , KC_RPRN  , KC_AMPR    ,
    KC_GRV         , KC_AT   , KC_BSLS       , KC_EXLM        , KC_QUES      ,                                      KC_LABK , KC_RABK    , KC_LCBR  , KC_RCBR  , KC_PIPE    ,
    XXXXXXX        , XXXXXXX , XXXXXXX       , XXXXXXX        , _______      , _______       , _______ ,            _______ , XXXXXXX    , XXXXXXX  , XXXXXXX  , XXXXXXX
  ),

  [3] = LAYOUT_universal(
    XXXXXXX        , XXXXXXX , XXXXXXX       , XXXXXXX        , XXXXXXX      ,                                      XXXXXXX , KC_KB_MUTE , KC_KB_VOLUME_DOWN , KC_KB_VOLUME_UP , XXXXXXX  ,
    XXXXXXX        , XXXXXXX , XXXXXXX       , XXXXXXX        , XXXXXXX      ,                                      XXXXXXX ,LCMD(KC_LEFT),LCMD(KC_RGHT), _______  , XXXXXXX    ,
    XXXXXXX        , XXXXXXX , XXXXXXX       , XXXXXXX        , XXXXXXX      ,                                      XXXXXXX , XXXXXXX    , MS_BTN1  , MS_BTN2  , XXXXXXX    ,
    XXXXXXX        , XXXXXXX , XXXXXXX       , XXXXXXX        , _______      , _______       , _______ ,            _______ , XXXXXXX    , XXXXXXX  , XXXXXXX  , XXXXXXX
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
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
