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

// Copied from https://github.com/qmk/qmk_firmware/commit/3c58f989295e17d03b66db9a154e02cde7336ece

#include "quantum.h"
#include "pmw3360.h"

#define PMW3360_SPI_MODE 3
#define PMW3360_CLOCKS 2000000

#define constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))

void spi_start() {
    setPinOutput(PMW3360_NCS_PIN);
    writePinLow(PMW3360_NCS_PIN);
    wait_us(1);
}

void spi_stop() {
    wait_us(1);
    setPinOutput(PMW3360_NCS_PIN);
    writePinHigh(PMW3360_NCS_PIN);
}

// clang-format off
bmp_api_spim_config_t config = {
    .freq = SPI_FREQ_2M,
    .miso = PMW3360_MISO,
    .mosi = PMW3360_MOSI,
    .sck  = PMW3360_SCLK,
    .mode = PMW3360_SPI_MODE
};
// clang-format on

uint8_t pmw3360_reg_read(uint8_t addr) {
    spi_start();
    // send adress of the register, with MSBit = 0 to indicate it's a read
    uint8_t snd = addr & 0x7f;
    BMPAPI->spim.start(&snd, 1, NULL, 0, 0xFF);
    // tSRAD (=160us)
    wait_us(160);
    uint8_t data = 0x00;
    BMPAPI->spim.start(NULL, 0, &data, 1, 0xFF);

    // tSCLK-NCS for read operation is 120ns
    wait_us(1);
    spi_stop();
    
    // tSRW/tSRR (=20us) minus tSCLK-NCS
    wait_us(19);
    return data;
}

void pmw3360_reg_write(uint8_t addr, uint8_t data) {
    spi_start();
    uint8_t snd[] = {addr | 0x80, data};
    BMPAPI->spim.start(snd, sizeof(snd), NULL, 0, 0xFF);

    // tSCLK-NCS for write operation is 35us
    wait_us(35);
    spi_stop();

    // tSWW/tSWR (=180us) minus tSCLK-NCS. Could be shortened, but it looks like a safe lower bound
    wait_us(180);
}

uint16_t pmw3360_cpi_get(void) {
    uint8_t cpival = pmw3360_reg_read(pmw3360_Config1);
    return (uint16_t)((cpival + 1) & 0xFF) * CPI_STEP;
}

void pmw3360_cpi_set(uint16_t cpi) {
    uint8_t cpival = constrain((cpi / CPI_STEP) - 1, 0, pmw3360_MAXCPI);
    pmw3360_reg_write(pmw3360_Config1, cpival);
}

static uint32_t pmw3360_timer      = 0;
static uint32_t pmw3360_scan_count = 0;
static uint32_t pmw3360_last_count = 0;

void pmw3360_scan_perf_task(void) {
    pmw3360_scan_count++;
    uint32_t now = timer_read32();
    if (TIMER_DIFF_32(now, pmw3360_timer) > 1000) {
#if defined(CONSOLE_ENABLE)
        dprintf("pmw3360 scan frequency: %lu\n", pmw3360_scan_count);
#endif
        pmw3360_last_count = pmw3360_scan_count;
        pmw3360_scan_count = 0;
        pmw3360_timer      = now;
    }
}

uint32_t pmw3360_scan_rate_get(void) {
    return pmw3360_last_count;
}

bool pmw3360_motion_read(pmw3360_motion_t *d) {
#ifdef DEBUG_PMW3360_SCAN_RATE
    pmw3360_scan_perf_task();
#endif
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
#ifdef DEBUG_PMW3360_SCAN_RATE
    pmw3360_scan_perf_task();
#endif
    spi_start();
    uint8_t snd = pmw3360_Motion_Burst;
    BMPAPI->spim.start(&snd, 1, NULL, 0, 0xFF);
    wait_us(35);

    uint8_t data[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    BMPAPI->spim.start(NULL, 0, data, sizeof(data), 0xFF);
    if ((data[0] & 0x88) != 0x80) {
        spi_stop();
        return false;
    }

    d->x = data[2];
    d->x |= data[3] << 8;
    d->y = data[4];
    d->y |= data[5] << 8;

    spi_stop();
    return true;
}

bool pmw3360_check_signature() {
    uint8_t pid      = pmw3360_reg_read(pmw3360_Product_ID);
    // uint8_t iv_pid   = pmw3360_reg_read(pmw3360_Revision_ID);
    // return pid == 0x42 && iv_pid == 0x01;
    uint8_t iv_pid   = pmw3360_reg_read(pmw3360_Inverse_Product_ID);
    uint8_t SROM_ver = pmw3360_reg_read(pmw3360_SROM_ID);
    return pid == 0x42 && iv_pid == 0xBD && SROM_ver == 0x04;
}

bool pmw3360_init(void) {
    BMPAPI->spim.init(&config);
    // spi_init();
    setPinOutput(PMW3360_NCS_PIN);

    // reboot
    // power up, need to first drive NCS high then low.
    // the datasheet does not say for how long, 40us works well in practice.
    spi_start();
    wait_us(40);
    spi_stop();
    wait_us(40);
    pmw3360_reg_write(pmw3360_Power_Up_Reset, 0x5a);
    wait_ms(50);

    // read five registers of motion and discard those values
    pmw3360_reg_read(pmw3360_Motion);
    pmw3360_reg_read(pmw3360_Delta_X_L);
    pmw3360_reg_read(pmw3360_Delta_X_H);
    pmw3360_reg_read(pmw3360_Delta_Y_L);
    pmw3360_reg_read(pmw3360_Delta_Y_H);

    pmw3360_reg_write(pmw3360_Config2, 0x00);

    // pmw3360_reg_write(pmw3360_Angle_Tune, constrain(ROTATIONAL_TRANSFORM_ANGLE, -127, 127));

    // pmw3360_reg_write(pmw3360_Lift_Config, PMW3360_LIFTOFF_DISTANCE);
    uint8_t pid   = pmw3360_reg_read(pmw3360_Product_ID);
    uint8_t rev   = pmw3360_reg_read(pmw3360_Revision_ID);
    spi_stop();
    return pid == 0x42 && rev == 0x01;
}
