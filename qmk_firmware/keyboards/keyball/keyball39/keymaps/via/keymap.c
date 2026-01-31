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

// Print screen for rectangle selection
#define PS_SELECT C(S(G(KC_4)))

// https://docs.qmk.fm/#/feature_tap_dance?id=simple-example
enum {
    TD_ESC,
};

tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Default (VIA) Keymap
  [0] = LAYOUT_universal(
    KC_Q         , KC_W         , KC_E         , KC_R         , KC_T         ,                               KC_Y         , KC_U         , KC_I         , KC_O         , KC_P         ,
    KC_A         , KC_S         , LT(4,KC_D)   , GUI_T(KC_F)  , KC_G         ,                               KC_H         , KC_J         , KC_K         , KC_L         , KC_MINS      ,
    KC_Z         , KC_X         , LT(3,KC_C)   , KC_V         , KC_B         ,                               KC_N         , KC_M         , KC_COMM      , KC_DOT       , KC_SLSH      ,
    TO(0)        , KC_LCTL      , KC_LALT      , LT(2,KC_LNG1), SFT_T(KC_SPC), LT(1,KC_LNG2), LT(3,KC_BSPC), GUI_T(KC_ENT), XXXXXXX      , XXXXXXX      , XXXXXXX      , PS_SELECT
  ),

  // Special Key Layer
  [1] = LAYOUT_universal(
    XXXXXXX      , S(KC_1)      , S(KC_2)      , S(KC_3)      , S(KC_4)      ,                               S(KC_5)      , S(KC_6)      , S(KC_7)      , S(KC_8)      , XXXXXXX      ,
    XXXXXXX      , KC_LBRC      , S(KC_LBRC)   , S(KC_9)      , KC_QUOT      ,                               KC_BSLS      , KC_EQL       , KC_SCLN      , KC_QUOT      , XXXXXXX      ,    
    XXXXXXX      , KC_RBRC      , S(KC_RBRC)   , S(KC_0)      , S(KC_QUOT)   ,                               S(KC_BSLS)   , S(KC_EQL)    , S(KC_SCLN)   , S(KC_QUOT)   , XXXXXXX      ,    
    _______      , _______      , _______      , _______      , _______      , _______      , _______      , _______      , XXXXXXX      , XXXXXXX      , XXXXXXX      , _______
  ),

  // Number Key Layer
  [2] = LAYOUT_universal(
    KC_F1        , KC_F2        , KC_F3        , KC_F4       , KC_F5         ,                               KC_F6        , KC_F7        , KC_F8        , KC_F9        , KC_F10       ,
    KC_1         , KC_2         , KC_3         , KC_4        , KC_5          ,                               KC_6         , KC_7         , KC_8         , KC_9         , KC_0         ,    
    KC_F11       , KC_F12       , XXXXXXX      , XXXXXXX     , XXXXXXX       ,                               XXXXXXX      , XXXXXXX      , KC_COMM      , KC_DOT       , KC_SLSH      ,    
    _______      , _______      , _______      , _______      , _______      , _______      , _______      , _______      , XXXXXXX      , XXXXXXX      , XXXXXXX      , _______
  ),

  // Arrow Key and Window Control Key Layer
  [3] = LAYOUT_universal(
    XXXXXXX      , C(A(KC_LEFT)), C(A(KC_ENT)) , C(A(KC_RGHT)), XXXXXXX      ,                               XXXXXXX      , XXXXXXX      , KC_UP        , XXXXXXX      , XXXXXXX      ,
    XXXXXXX      , G(KC_LBRC)   , XXXXXXX      , G(KC_RBRC)   , XXXXXXX      ,                               XXXXXXX      , KC_LEFT      , KC_DOWN      , KC_RGHT      , XXXXXXX      ,    
    XXXXXXX      , C(KC_LEFT)   , C(KC_UP)     , C(KC_RGHT)   , XXXXXXX      ,                               XXXXXXX      , KC_TAB       , KC_ESC       , S(KC_TAB)    , XXXXXXX      ,    
    _______      , _______      , _______      , _______      , _______      , _______      , _______      , _______      , XXXXXXX      , XXXXXXX      , XXXXXXX      , _______
  ),

  // Programming Key Layer
  [4] = LAYOUT_universal(
    XXXXXXX      , S(G(KC_P))   , C(KC_R)      , KC_F2        , XXXXXXX      ,                                XXXXXXX     , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      ,
    XXXXXXX      , C(KC_MINS)   , C(KC_GRV)    , KC_F12       , S(G(KC_V))   ,                                XXXXXXX     , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      ,    
    XXXXXXX      , C(KC_A)      , C(KC_C)      , C(KC_E)      , C(KC_L)      ,                                XXXXXXX     , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      ,    
    _______      , _______      , _______      , _______      , _______      , _______      , _______      , _______      , XXXXXXX      , XXXXXXX      , XXXXXXX      , _______

  ),

  // Keyball Key Layer
  [5] = LAYOUT_universal(
    XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      ,                                XXXXXXX     , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      ,    
    XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      ,                                XXXXXXX     , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      ,    
    XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      ,                                XXXXXXX     , XXXXXXX      , XXXXXXX      , XXXXXXX      , XXXXXXX      ,    
    _______      , _______      , _______      , _______      , _______      , _______      , _______      , _______      , XXXXXXX      , XXXXXXX      , XXXXXXX      , _______
  ),

  // Mouse Key Layer
  [6] = LAYOUT_universal(
    _______      , _______      , _______      , _______      , _______      ,                                XXXXXXX     , XXXXXXX      , XXXXXXX      , XXXXXXX     , XXXXXXX      ,    
    _______      , _______      , _______      , _______      , _______      ,                                XXXXXXX     , KC_MS_BTN1   , SCRL_MO      , KC_MS_BTN2  , XXXXXXX      ,    
    _______      , _______      , _______      , _______      , _______      ,                                XXXXXXX     , XXXXXXX      , XXXXXXX      , XXXXXXX     , XXXXXXX      ,    
    _______      , _______      , _______      , _______      , _______      , _______      , _______      , _______      , XXXXXXX      , XXXXXXX      , XXXXXXX      , _______
  ),
};

// clang-format on

/**
 * https://docs.qmk.fm/#/feature_pointing_device?id=pointing-device-auto-mouse
 */
void pointing_device_init_user(void) {
    set_auto_mouse_enable(true);
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
