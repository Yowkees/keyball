/*
This is the c configuration file for the keymap

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

#pragma once

#ifdef RGBLIGHT_ENABLE
//#    define RGBLIGHT_EFFECT_BREATHING
//#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
//#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//#    define RGBLIGHT_EFFECT_SNAKE
//#    define RGBLIGHT_EFFECT_KNIGHT
//#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
//#    define RGBLIGHT_EFFECT_RGB_TEST
//#    define RGBLIGHT_EFFECT_ALTERNATING
//#    define RGBLIGHT_EFFECT_TWINKLE
#endif

#define TAP_CODE_DELAY 5

#define TAPPING_TERM 150

// #define DYNAMIC_KEYMAP_LAYER_COUNT 7

#define DYNAMIC_KEYMAP_LAYER_COUNT 5
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
// Time layer remains active after activation
#define AUTO_MOUSE_TIME 250
// #define AUTO_MOUSE_TIME 450

#define _LAYER_HOME_LAYER 0
#define _LAYER_NUMBER_LAYER 1
#define _LAYER_SYMBOL_LAYER 2
#define _LAYER_MOUSE_CLICK_LAYER 3
#define _LAYER_MOUSE_SCROLL_LAYER 4

#define AUTO_MOUSE_DEFAULT_LAYER _LAYER_MOUSE_CLICK_LAYER
