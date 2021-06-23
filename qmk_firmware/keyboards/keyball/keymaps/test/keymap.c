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

#include "pointing_device.h"
#include "trackball.h"
#include "oledkit.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

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

#if 0
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

static int8_t ball1_x = 0, ball1_y = 0;
static int8_t ball2_x = 0, ball2_y = 0;

void trackball_process_user(int8_t dx, int8_t dy) {
    ball1_x = dx;
    ball1_y = dy;
    // apply events to pointer always on primary trackball.
    report_mouse_t r = pointing_device_get_report();
    r.x = dx;
    r.y = dy;
    pointing_device_set_report(r);
}

void trackball_process_secondary_user(int8_t dx, int8_t dy) {
    ball2_x = dx;
    ball2_y = dy;
    // aplly events to scroll always on secondary trackball.
    report_mouse_t r = pointing_device_get_report();
    r.h = dx;
    r.v = -dy;
    pointing_device_set_report(r);
}

#ifdef OLED_DRIVER_ENABLE

void oledkit_render_info_user(void) {
    static char buf[11] = {0};

    // primary trackball's status
    oled_write_P(PSTR("B1: "), false);
    snprintf(buf, sizeof(buf), "%d, %d", ball1_x, ball1_y);
    oled_write_ln(buf, false);

    // secondary trackball's status
    oled_write_P(PSTR("B2: "), false);
    snprintf(buf, sizeof(buf), "%d, %d", ball2_x, ball2_y);
    oled_write_ln(buf, false);
}

#endif
