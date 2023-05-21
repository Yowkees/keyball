/*
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

#include <string.h>
#include "quantum.h"
#include "matrix.h"
#include "bmp_matrix.h"
#include "apidef.h"

uint32_t get_device_row() { return BMPAPI->app.get_config()->matrix.rows; };
uint32_t get_device_col() { return BMPAPI->app.get_config()->matrix.cols; };

static inline void set_pin_input(uint8_t pin) {
    setPinInputHigh(pin);
}

static void set_pins_input(const uint8_t *pins, uint8_t n) {
    for (uint8_t i = 0; i < n; i++) {
        set_pin_input(pins[i]);
    }
}

static inline void set_pin_output(uint8_t pin) {
    setPinOd(pin);
    writePinHigh(pin);
}

static inline bool get_pin(const uint8_t pin) {
    if (pin == 0) {
        return false;
    }
    return BMPAPI->gpio.read_pin(pin);
}

static inline void select_pin(const uint8_t pin) {
    if (pin != 0) {
        BMPAPI->gpio.clear_pin(pin);
    }
}

static inline void unselect_pin(const uint8_t pin) {
    if (pin != 0) {
        BMPAPI->gpio.set_pin(pin);
    }
}

uint32_t duplex_scan(matrix_row_t *current_matrix) {
    uint32_t changed = 0;
    const bmp_api_config_t *config = BMPAPI->app.get_config();

    uint32_t pinnum_rows = config->matrix.device_rows;
    uint32_t pinnum_cols = config->matrix.device_cols;

    // scan column to row
    for (uint8_t row = 0; row < pinnum_rows; row++) {
        set_pin_output(config->matrix.row_pins[row]);
        select_pin(config->matrix.row_pins[row]);
        matrix_row_t next = current_matrix[row];
        for (uint8_t col = 0; col < pinnum_cols; col++) {
            bool on = !get_pin(config->matrix.col_pins[col]);
            if (on) {
                next |= 1 << col;
            } else {
                next &= ~(1 << col);
            }
        }
        set_pin_input(config->matrix.row_pins[row]);
        unselect_pin(config->matrix.row_pins[row]);
        if (current_matrix[row] != next) {
            current_matrix[row] = next;
            changed             = 1;
        }
    }

    // scan row to column.
    for (uint8_t col = 0; col < pinnum_cols; col++) {
        set_pin_output(config->matrix.col_pins[col]);
        select_pin(config->matrix.col_pins[col]);
        matrix_row_t shifter = ((matrix_row_t)1) << (col + pinnum_cols);
        for (uint8_t row = 0; row < pinnum_rows; row++) {
            bool         on   = !get_pin(config->matrix.row_pins[row]);
            matrix_row_t prev = current_matrix[row];
            if (on) {
                current_matrix[row] |= shifter;
            } else {
                current_matrix[row] &= ~shifter;
            }
            if (current_matrix[row] != prev) {
                changed = 1;
            }
        }
        set_pin_input(config->matrix.col_pins[col]);
        unselect_pin(config->matrix.col_pins[col]);
    }

    return changed;
}

void matrix_init_custom(void) {
    const bmp_api_config_t *config = BMPAPI->app.get_config();

    set_pins_input(config->matrix.col_pins, config->matrix.device_cols);
    set_pins_input(config->matrix.row_pins, config->matrix.device_rows);
}

static const bmp_matrix_func_t matrix_func = {
    matrix_init_custom, get_device_row, get_device_col, duplex_scan};

const bmp_matrix_func_t *get_matrix_func_user() { return &matrix_func; }