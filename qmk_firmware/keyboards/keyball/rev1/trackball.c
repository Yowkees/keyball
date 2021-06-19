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

__attribute__((weak)) void pointing_device_init(void) {
    if (is_keyboard_master()){
        optical_sensor_init();
    }
}

static bool is_scroll_mode;

static int8_t clamp(int16_t value) {
    return value < -128 ? -128 : value > 127 ? 127 : (int8_t)value;
}

__attribute__((weak)) void pointing_device_task(void) {
    // TODO: support for secondary.
    if (!is_keyboard_master())
        return;

    // Trackball uses mean value of N samples from optical sensor as delta for
    // mouse cursor or scroll.  Number of samples are determined by
    // TRACKBALL_SAMPLE_COUNT.

    static int16_t accum_count = 0;
    static int16_t accum_x = 0, accum_y = 0;

    report_optical_sensor_t sensor_report = optical_sensor_get_report();
    accum_x += sensor_report.x;
    // sensor returns negative values for downward rotation, but screen has
    // positive axis for downward, so we invert the sign of Y.
    accum_y -= sensor_report.y;
    accum_count++;

    if (accum_count >= TRACKBALL_SAMPLE_COUNT) {
        int8_t dx = clamp(accum_x / accum_count);
        int8_t dy = clamp(accum_y / accum_count);
        if (dx != 0 || dy != 0) {
            trackball_process_delta_user(dx, dy);
        }
        // clear accumulation variables.
        accum_x = 0;
        accum_y = 0;
        accum_count = 0;
    }

    pointing_device_send();
}

__attribute__((weak)) void trackball_process_delta_user(int8_t dx, int8_t dy) {
    report_mouse_t r = pointing_device_get_report();
    if (is_scroll_mode) {
        r.h = dx / TRACKBALL_SCROLL_DIVIDER;
        r.v = -dy / TRACKBALL_SCROLL_DIVIDER;
    } else {
        r.x = dx;
        r.y = dy;
    }
    pointing_device_set_report(r);
}

bool trackball_get_scroll_mode(void) {
    return is_scroll_mode;
}

void trackball_set_scroll_mode(bool mode) {
    is_scroll_mode = mode;
}

#endif // TRACKBALL_DRIVER_DISABLE
