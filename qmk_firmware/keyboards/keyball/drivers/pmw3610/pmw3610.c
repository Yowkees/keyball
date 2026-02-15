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

Modifications 2025 by Nobuki Inoue (your @black_trooper)
- Added support for PMW3610
*/

#include "quantum.h"
#include "pmw3610.h"

#define TOINT16(val, bits) (((struct { int16_t value : bits; }){val}).value)
#define CONSTRAIN_HID_XY(amt) ((amt) < XY_REPORT_MIN ? XY_REPORT_MIN : ((amt) > XY_REPORT_MAX ? XY_REPORT_MAX : (amt)))

void pmw3610_spi_start(void) {
    writePinLow(PMW3610_NCS_PIN);
    wait_us(1);
}

void pmw3610_spi_stop(void) {
    writePinHigh(PMW3610_NCS_PIN);
}

uint8_t pmw3610_reg_read(uint8_t reg_addr) {
    pmw3610_spi_start();

    setPinOutput(PMW3610_SDIO_PIN);
    for (int8_t i = 7; i >= 0; i--) {
        writePinLow(PMW3610_SCLK_PIN);
        writePin(PMW3610_SDIO_PIN, reg_addr & (1 << i));
        wait_us(1);
        writePinHigh(PMW3610_SCLK_PIN);
        wait_us(1);
    }
    setPinInput(PMW3610_SDIO_PIN);
    wait_us(4);
    uint8_t data = 0;
    for (int8_t i = 7; i >= 0; i--) {
        writePinLow(PMW3610_SCLK_PIN);
        wait_us(1);
        writePinHigh(PMW3610_SCLK_PIN);
        wait_us(1);
        data |= readPin(PMW3610_SDIO_PIN) << i;
    }
    wait_us(1);
    pmw3610_spi_stop();

    wait_us(1);
    return data;
}

void pmw3610_write_byte(uint8_t byte) {
    setPinOutput(PMW3610_SDIO_PIN);

    for (int8_t i = 7; i >= 0; i--) {
        writePinLow(PMW3610_SCLK_PIN);

        if (byte & (1 << i)) {
            writePinHigh(PMW3610_SDIO_PIN);
        } else {
            writePinLow(PMW3610_SDIO_PIN);
        }

        wait_us(1);

        writePinHigh(PMW3610_SCLK_PIN);
        wait_us(1);
    }

    writePinLow(PMW3610_SCLK_PIN);
}

void pmw3610_reg_write(uint8_t reg_addr, uint8_t data) {
    // SPI Clock On (Enable SPI Clock)
    pmw3610_spi_start();
    pmw3610_write_byte(PMW3610_SPI_CLK_ON_REQ | 0x80);
    pmw3610_write_byte(0xBA);
    pmw3610_spi_stop();
    wait_us(300);

    // Write actual register value
    pmw3610_spi_start();
    pmw3610_write_byte(reg_addr | 0x80);
    pmw3610_write_byte(data);
    pmw3610_spi_stop();

    // SPI Clock Off (Power saving)
    pmw3610_spi_start();
    pmw3610_write_byte(PMW3610_SPI_CLK_ON_REQ | 0x80);
    pmw3610_write_byte(0xB5);
    pmw3610_spi_stop();

    wait_us(20);
}

void pmw3610_cpi_set(uint8_t cpi) {
    if (cpi > pmw3610_MAXCPI) {
        cpi = pmw3610_MAXCPI;
    }

    pmw3610_reg_write(PMW3610_SPI_PAGE0, 0xFF);
    pmw3610_reg_write(PMW3610_RES_STEP, cpi);
    pmw3610_reg_write(PMW3610_SPI_PAGE1, 0x00);
}

bool pmw3610_motion_read(pmw3610_motion_t *d) {
    uint8_t mot = pmw3610_reg_read(PMW3610_MOTION);
    if (!(mot & 0x80)) {
        return false;
    }
    uint8_t xl  = pmw3610_reg_read(PMW3610_DELTA_X_L);
    uint8_t yl  = pmw3610_reg_read(PMW3610_DELTA_Y_L);
    uint8_t xyh = pmw3610_reg_read(PMW3610_DELTA_XY_H);
    uint8_t xh = (xyh & 0xF0) >> 4;
    uint8_t yh = (xyh & 0x0F);
    
    int16_t dx = TOINT16((xl | (xh << 8)), 12);
    int16_t dy = TOINT16((yl | (yh << 8)), 12);

    d->x = CONSTRAIN_HID_XY(dx);
    d->y = CONSTRAIN_HID_XY(dy);

    return true;
}

bool pmw3610_init(void) {
    debug_enable = true;
    setPinOutput(PMW3610_SCLK_PIN);
    setPinOutput(PMW3610_SDIO_PIN);
    setPinOutput(PMW3610_NCS_PIN);
    // reboot
    pmw3610_spi_start();
    pmw3610_reg_write(PMW3610_POWER_UP_RESET, 0x5a);
    pmw3610_spi_stop();
    wait_ms(50);
    // read five registers of motion and discard those values
    pmw3610_reg_read(PMW3610_MOTION);
    pmw3610_reg_read(PMW3610_DELTA_X_L);
    pmw3610_reg_read(PMW3610_DELTA_Y_L);
    pmw3610_reg_read(PMW3610_DELTA_XY_H);
    pmw3610_reg_read(PMW3610_RES_STEP);
    // check product ID and revision ID
    uint8_t pid = pmw3610_reg_read(PMW3610_PROD_ID);
    uint8_t rev = pmw3610_reg_read(PMW3610_REV_ID);
    spi_stop();

    wait_us(1000);
    return pid == 0x3E && rev == 0x01;
}