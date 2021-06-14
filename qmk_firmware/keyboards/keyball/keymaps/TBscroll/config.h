/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

#pragma once

#define PMW_3360

//#define USE_MATRIX_I2C

/* Select hand configuration */

//#define MASTER_LEFT
#define MASTER_RIGHT
// #define EE_HANDS

#define SOFT_SERIAL_PIN D2

#define TAPPING_TERM 180
#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_TERM_PER_KEY

#undef MOUSEKEY_INTERVAL
#undef MOUSEKEY_DELAY
#undef MOUSEKEY_TIME_TO_MAX
#undef MOUSEKEY_MAX_SPEED
#undef MOUSEKEY_MOVE_DELTA
#define MOUSEKEY_INTERVAL 20
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_TIME_TO_MAX 20
#define MOUSEKEY_MAX_SPEED 8
#define MOUSEKEY_MOVE_DELTA 2

/*
#define MK_3_SPEED
#define MK_C_OFFSET_0 6
#define MK_C_INTERVAL_0 16
#define MK_C_OFFSET_1 12
#define MK_C_INTERVAL_1 16
#define MK_C_OFFSET_2 18
#define MK_C_INTERVAL_2 16
*/

#ifdef RGBLIGHT_ENABLE
    #undef RGBLED_NUM
//    #define RGBLIGHT_ANIMATIONS
    #define RGBLED_NUM 7
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif

#define OLED_FONT_H "keyboards/claw44/lib/glcdfont.c"

