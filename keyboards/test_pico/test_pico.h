#pragma once

#include <i2c_master.h>
#include <stdint.h>
#include <stdbool.h>

#define SLAVE_I2C_ADDRESS_RIGHT (0x76 << 1)
#define SLAVE_I2C_ADDRESS_LEFT (0x77 << 1)

#define MAIN_ROWS 2
#define MAIN_COLS 2
#define LEFT_ROWS 2
#define LEFT_COLS 2
#define RIGHT_ROWS 2
#define RIGHT_COLS 2


void i2c_initialize(void);
bool isI2C_initialized(void);

void i2c_select_row(uint8_t row_index);
void i2c_select_row_on(uint8_t addr, uint8_t row_index);