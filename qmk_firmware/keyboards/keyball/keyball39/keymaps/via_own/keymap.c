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
#include "layer.h"
#include "tap_dance.h"
#include "layer_lighting.h"



#ifdef TAP_DANCE_ENABLE
//Tap dance enums
enum {
  CTL_ALT = 0
};
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [_DEFAULT_LAYER] = LAYOUT_universal(
    KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     ,
    KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , KC_K     , KC_L     , KC_DOT  ,
    KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , KC_BTN1 , LT(3,KC_BTN2)   , KC_COMM  ,
    TD(CTL_ALT)  , KC_LGUI  , KC_ESC  ,LT(3,KC_TAB),LT(1,KC_SPC),LT(2,KC_DELETE),                 LT(1,KC_ENT),LT(2,KC_BSPC),_______,_______,_______, TD(CTL_ALT)
  ),

  [_OPERATION_LAYER] = LAYOUT_universal(
    _______  , KC_7  , KC_8 , KC_9 , S(KC_SCLN) ,                           C(KC_HOME) , C(KC_PGDN) , C(KC_PGUP) , C(KC_END), _______   ,
    KC_0     , KC_4  , KC_5 , KC_6 , KC_MINUS   ,                           KC_LEFT, KC_DOWN  , KC_UP  , KC_RIGHT  , _______  ,
    _______  , KC_1  , KC_2 , KC_3 , KC_DOT     ,                           KC_HOME  , KC_PGDN   , KC_PGUP  , KC_END  , _______   ,
    TD(CTL_ALT)  , _______   , _______  , _______  , _______  , _______  ,               _______  ,_______ , _______  , _______  , _______  , TD(CTL_ALT)
  ),

  [_SYMBOL_LAYER] = LAYOUT_universal(
    KC_GRV    , S(KC_4) , S(KC_5) , S(KC_7)   , S(KC_BSLS),                            S(KC_MINUS) , S(KC_LBRC)  , S(KC_RBRC)  , S(KC_COMM)  , S(KC_DOT)  ,
    S(KC_2)   , S(KC_3) , S(KC_8) , S(KC_EQL) , KC_EQL    ,                            KC_MINUS    , S(KC_9)  , S(KC_0)  , S(KC_SCLN)  , KC_SCLN  ,
    S(KC_GRV) , S(KC_6) , KC_BSLS , S(KC_1)   , S(KC_SLSH),                            KC_SLSH     , KC_LBRC  , KC_RBRC  , KC_QUOT  , S(KC_QUOT)  ,
    TD(CTL_ALT) , _______ , _______ , _______ , _______   , _______  ,      _______  , _______  , _______  , _______  , _______  , TD(CTL_ALT)
  ),

  [_MOUSE_LAYER] = LAYOUT_universal(
    KC_CAPS  , KC_F7   , KC_F8  , KC_F9  , KC_F11  ,                            SSNP_VRT  , SSNP_HOR  , SSNP_FRE , _______ , _______ ,
    KC_F10  , KC_F4  , KC_F5  , KC_F6  , KC_F12 ,                            _______  , _______  , _______  , _______  , _______  ,
    _______ , KC_F1  , KC_F2  , KC_F3  , KC_PSCR ,                            RCS(KC_T)  , C(KC_T) , C(KC_W) , _______  , RCS(KC_BTN1) ,
    TD(CTL_ALT)  , _______  , _______  , _______  , _______  , _______  ,      KC_BTN5  , KC_BTN4  , _______  , _______  , _______ , TD(CTL_ALT)
  ),
};
// clang-format on

// Layer lighting
void keyboard_post_init_user(void) {
    rgblight_layers = light_layers;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(LAYER_LIGHTING_CAPSLOCK, led_state.caps_lock);
    return true;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(LAYER_LIGHTING_DEFAULT, layer_state_cmp(state, _DEFAULT_LAYER));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == _MOUSE_LAYER);

    rgblight_set_layer_state(LAYER_LIGHTING_OPERATION, layer_state_cmp(state, _OPERATION_LAYER));
    rgblight_set_layer_state(LAYER_LIGHTING_SYMBOL, layer_state_cmp(state, _SYMBOL_LAYER));

    keyball_scrollsnap_mode_t mode = keyball_get_scrollsnap_mode();
    rgblight_set_layer_state(LAYER_LIGHTING_MOUSE_VRT, layer_state_cmp(state, _MOUSE_LAYER) && (mode == KEYBALL_SCROLLSNAP_MODE_VERTICAL));
    rgblight_set_layer_state(LAYER_LIGHTING_MOUSE_HOR, layer_state_cmp(state, _MOUSE_LAYER) && (mode == KEYBALL_SCROLLSNAP_MODE_HORIZONTAL));
    rgblight_set_layer_state(LAYER_LIGHTING_MOUSE_FRE, layer_state_cmp(state, _MOUSE_LAYER) && (mode == KEYBALL_SCROLLSNAP_MODE_FREE));
    return state;
}

// Tap dance
#ifdef TAP_DANCE_ENABLE
tap_dance_action_t tap_dance_actions[] = {
  [CTL_ALT]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,ctlalt_finished, ctlalt_reset)
};
#endif

// OLED
#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
