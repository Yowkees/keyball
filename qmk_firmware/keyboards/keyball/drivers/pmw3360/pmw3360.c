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

#include "quantum.h"
#include "pmw3360.h"

#define PMW3360_SPI_MODE 3
#define PMW3360_SPI_DIVISOR (F_CPU / PMW3360_CLOCKS)
#define PMW3360_CLOCKS 70000000

bool pmw3360_spi_start(void) { return spi_start(PMW3360_NCS_PIN, false, PMW3360_SPI_MODE, PMW3360_SPI_DIVISOR); }

uint8_t pmw3360_reg_read(uint8_t addr) {
    pmw3360_spi_start();
    spi_write(addr & 0x7f);
    wait_us(160);
    uint8_t data = spi_read();
    spi_stop();
    wait_us(20);
    return data;
}

void pmw3360_reg_write(uint8_t addr, uint8_t data) {
    pmw3360_spi_start();
    spi_write(addr | 0x80);
    spi_write(data);
    spi_stop();
    wait_us(180);
}

uint16_t pmw3360_cpi_get(void) {
    uint8_t cpi8 = pmw3360_reg_read(pmw3360_Config1);
    return ((uint16_t)cpi8 + 1) * 100;
}

void pmw3360_cpi_set(uint16_t cpi) {
    if (cpi < pmw3360_MINCPI) {
        cpi = pmw3360_MINCPI;
    } else if (cpi > pmw3360_MAXCPI) {
        cpi = pmw3360_MAXCPI;
    }
    pmw3360_reg_write(pmw3360_Config1, (uint8_t)((cpi / 100) - 1));
}

bool pmw3360_motion_read(pmw3360_motion_t *d) {
    uint8_t mot = pmw3360_reg_read(pmw3360_Motion);
    if ((mot & 0x88) != 0x80) {
        return false;
    }
    d->x = pmw3360_reg_read(pmw3360_Delta_X_L);
    d->x |= pmw3360_reg_read(pmw3360_Delta_X_H) << 8;
    d->y = pmw3360_reg_read(pmw3360_Delta_Y_L);
    d->y |= pmw3360_reg_read(pmw3360_Delta_Y_H) << 8;
    return true;
}

bool pmw3360_motion_burst(pmw3360_motion_t *d) {
    pmw3360_spi_start();
    spi_write(pmw3360_Motion_Burst);
    wait_us(35);
    uint8_t mot = spi_read();
    if ((mot & 0x88) != 0x80) {
        spi_stop();
        return false;
    }
    spi_read(); // skip Observation
    d->x = spi_read();
    d->x |= spi_read() << 8;
    d->y = spi_read();
    d->y |= spi_read() << 8;
    spi_stop();
    return true;
}

bool pmw3360_init(void) {
    spi_init();
    setPinOutput(PMW3360_NCS_PIN);
    // reboot
    pmw3360_spi_start();
    pmw3360_reg_write(pmw3360_Power_Up_Reset, 0x5a);
    wait_ms(50);
    // read five registers of motion and discard those values
    pmw3360_reg_read(pmw3360_Motion);
    pmw3360_reg_read(pmw3360_Delta_X_L);
    pmw3360_reg_read(pmw3360_Delta_X_H);
    pmw3360_reg_read(pmw3360_Delta_Y_L);
    pmw3360_reg_read(pmw3360_Delta_Y_H);
    // configuration
    pmw3360_reg_write(pmw3360_Config2, 0x00);
    // check product ID and revision ID
    uint8_t pid = pmw3360_reg_read(pmw3360_Product_ID);
    uint8_t rev = pmw3360_reg_read(pmw3360_Revision_ID);
    spi_stop();
    return pid == 0x42 && rev == 0x01;
}
