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

#pragma once

#ifndef TRACKBALL_DRIVER_DISABLE

#include <stdint.h>

#define TRACKBALL_DELTA_DIMENSION 2

// trackball_has should returns status of trackball availability.  it delegates
// is_keyboard_master() as default, but it can be overridden by keyboards or
// keymaps.
bool trackball_has(void);

// trackball_process_user will be callbacked when trackball detects some
// rotation. User can override default behavior of trackball by defining this
// function.
void trackball_process_user(int8_t dx, int8_t dy);

// trackball_process_secondary_user will be callbacked when a trackball on
// secondary board detects some rotation. User can override default behavior of
// trackball by defining this function.
void trackball_process_secondary_user(int8_t dx, int8_t dy);

// trackball_get_scroll_mode returns current scroll ode of trackball.
bool trackball_get_scroll_mode(void);

// trackball_set_scroll_mode enables/disables scroll mode of trackball.
// When scroll mode enabled, rotating trackball reports scrolling events.
void trackball_set_scroll_mode(bool mode);

// trackball_latest_delta gets latest detected rotation amount with stabilized.
// delta's size should be 2 or longer.
void trackball_latest_delta(int8_t* delta);

#endif // TRACKBALL_DRIVER_DISABLE
