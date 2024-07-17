#pragma once

#include <i2c_master.h>
#include <stdint.h>
#include <stdbool.h>

#define MY_I2C_ADDRESS (0x18 << 1)
#define MAIN_I2C_ADDRESS (0x18 << 1)
#define RIGHT_I2C_ADDRESS (0x19 << 1)
#define LEFT_I2C_ADDRESS (0x20 << 1)


void i2c_initialize(void);
bool isI2C_initialized(void);

void i2c_select_row(uint8_t row_index);
void i2c_select_row_on(uint8_t addr, uint8_t row_index);