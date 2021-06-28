/*
Copyright 2021 @Yowkees
Copyright 2021 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#include <stdio.h>

#include "oledkit.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

#if 0
  // Test keymap for double balls configuration.
  [0] = LAYOUT_double_balls(
   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_MINS,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
   //|--------+--------+--------+--------+--------+--------'                    `--------+--------+--------+--------+--------+--------|
        KC_ESC,  KC_GRV, KC_LALT,        KC_BSPC,  KC_SPC,                           KC_ENT,  KC_DEL,        KC_LBRC, KC_RBRC, KC_BSLS 
   //`--------+--------+--------'      `--------+--------'                        `--------+--------'      `--------+--------+--------'
  ),
#endif

#if 1
  [0] = LAYOUT_right_ball(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_LBRC,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         KC_A,    KC_S,    KC_D,    KC_F,    KC_G, KC_RBRC,                         KC_H,    KC_J,    KC_K,    KC_L, KC_MINS, KC_SCLN,
  //|--------+--------+--------+--------+--------+--------'                    |--------+--------+--------+--------+--------+--------|
         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                  KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_BSLS,
  //|--------+--------+--------+--------+--------+-------+--------.            `--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_LALT,    KC_BSPC,     KC_SPC,   KC_LGUI,  KC_ESC,                 KC_ENT,  KC_DEL,        KC_EXLM,  KC_TAB, KC_RSFT
  //`--------+--------'  `--------'  `--------' `--------+--------'              `--------+--------'      `--------+--------+--------'
  ),
#endif

};

void keyboard_post_init_user() {
#ifdef RGBLIGHT_ENABLE
    // Force RGB lights to show test animation without writing toi EEPROM.
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_RGB_TEST);
#endif
}

#ifdef OLED_DRIVER_ENABLE

static trackball_delta_t ball1, ball2;

void keyball_process_trackball_user(
        const trackball_delta_t *primary,
        const trackball_delta_t *secondary) {
    ball1 = *primary;
    ball2 = *secondary;
    keyball_process_trackball_default(primary, secondary);
}

void oledkit_render_info_user(void) {
    static char buf[22] = {0};

    // primary trackball's status
    oled_write_P(PSTR("Ball#1: "), false);
    snprintf(buf, sizeof(buf), "%d, %d", ball1.x, ball1.y);
    oled_write_ln(buf, false);

    // secondary trackball's status
    oled_write_P(PSTR("Ball#2: "), false);
    snprintf(buf, sizeof(buf), "%d, %d", ball2.x, ball2.y);
    oled_write_ln(buf, false);
}

#endif
