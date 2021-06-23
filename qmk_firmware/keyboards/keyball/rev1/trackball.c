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

#ifndef TRACKBALL_DRIVER_DISABLE

#include "quantum.h"
#include "pointing_device.h"

#include "optical_sensor/optical_sensor.h"
#include "trackball.h"

#ifndef TRACKBALL_SAMPLE_COUNT
#    define TRACKBALL_SAMPLE_COUNT 10
#endif
#if TRACKBALL_SAMPLE_COUNT <= 0
#    error "TRACKBALL_SAMPLE_COUNT should be larger than zero"
#endif

#ifndef TRACKBALL_SCROLL_DIVIDER
#    define TRACKBALL_SCROLL_DIVIDER 10
#endif
#if TRACKBALL_SCROLL_DIVIDER <= 0
#    error "TRACKBALL_SCROLL_DIVIDER should be larger than zero"
#endif

static bool is_primary = false;
static bool is_scroll_mode = false;

static int16_t accum_count = 0;
static int16_t accum_x = 0;
static int16_t accum_y = 0;

static int8_t delta_x = 0;
static int8_t delta_y = 0;

__attribute__((weak)) bool trackball_has(void) {
    // FIXME: support for secondary.
    return is_keyboard_master();
}

__attribute__((weak)) void pointing_device_init(void) {
    if (trackball_has()){
        optical_sensor_init();
        is_primary = is_keyboard_master();
    }
}

// clip2int8 clips an integer fit into int8_t.
static inline int8_t clip2int8(int16_t v) {
    return (v) < -128 ? -128 : (v) > 127 ? 127 : (int8_t)v;
}

// add16 adds two int16_t with clipping.
static int16_t add16(int16_t a, int16_t b) {
    int16_t r = a + b;
    if (a >= 0 && b >= 0 && r < 0) {
        r = 32767;
    } else if (a < 0 && b < 0 && r >= 0) {
        r = -32768;
    }
    return r;
}

__attribute__((weak)) void pointing_device_task(void) {
    if (!trackball_has())
        return;

    // Trackball uses mean value of N samples from optical sensor as delta for
    // mouse cursor or scroll.  Number of samples are determined by
    // TRACKBALL_SAMPLE_COUNT.
    //
    // The sensor returns negative values for downward rotation, but screen has
    // positive axis for downward, so we invert the sign of Y.
    report_optical_sensor_t sensor_report = optical_sensor_get_report();
    accum_x = add16(accum_x, sensor_report.x);
    accum_y = add16(accum_y, -sensor_report.y);
    accum_count++;

    if (accum_count >= TRACKBALL_SAMPLE_COUNT) {
        // divice to calculate mean value and clip it to fit into int8_t.
        int16_t div = (is_scroll_mode || !is_primary) ? TRACKBALL_SAMPLE_COUNT * TRACKBALL_SCROLL_DIVIDER : TRACKBALL_SAMPLE_COUNT;
        delta_x = clip2int8(accum_x / div);
        delta_y = clip2int8(accum_y / div);
        // clear accumulators with considering surplus.
        accum_x %= div;
        accum_y %= div;
        accum_count = 0;
        // process delta.
        if (is_primary && (delta_x != 0 || delta_y != 0)) {
            trackball_process_user(delta_x, delta_y);
        }
    } else {
        delta_x = 0;
        delta_y = 0;
    }

    pointing_device_send();
}

__attribute__((weak)) void trackball_process_user(int8_t dx, int8_t dy) {
    report_mouse_t r = pointing_device_get_report();
    if (is_scroll_mode) {
        r.h = dx;
        r.v = -dy;
    } else {
        r.x = dx;
        r.y = dy;
    }
    pointing_device_set_report(r);
}

__attribute__((weak)) void trackball_process_secondary_user(int8_t dx, int8_t dy) {
    // treat events as scroll always on secondary trackball.
    report_mouse_t r = pointing_device_get_report();
    r.h = dx;
    r.v = -dy;
    pointing_device_set_report(r);
}

bool trackball_get_scroll_mode(void) {
    return is_scroll_mode;
}

void trackball_set_scroll_mode(bool mode) {
    if (is_scroll_mode != mode) {
        is_scroll_mode = mode;
        // reset accumulators when scroll mode is changed.
        accum_count = 0;
        accum_x = 0;
        accum_y = 0;
    }
}

void trackball_latest_delta(int8_t* delta) {
    delta[0] = delta_x;
    delta[1] = delta_y;
}

#endif // TRACKBALL_DRIVER_DISABLE
