/**
  ******************************************************************************
  * @file    max6675.c
  * @brief   MAX6675 K-type thermocouple IC driver
  ******************************************************************************
  */
#include "max6675.h"
#include "bsp_spi.h"

static bool last_open;

void max6675_init(void) { last_open = false; }

bool max6675_read_temp(float *temp_c)
{
    uint8_t buf[2];
    if (!bsp_spi_receive(buf, 2, 100)) { last_open = true; if (temp_c) *temp_c = 0; return false; }
    uint16_t raw = ((uint16_t)buf[0] << 8) | buf[1];
    if (raw & 0x0004) { last_open = true; if (temp_c) *temp_c = 0; return false; }
    last_open = false;
    if (temp_c) *temp_c = (float)((raw >> 3) & 0x0FFF) * 0.25f;
    return true;
}

bool max6675_is_open_circuit(void) { return last_open; }
