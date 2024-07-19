#pragma once

//#include "config_common.h"
//#define DESCRIPTION three way split test on RP2040

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // Timeout window in ms in which the double tap can occur.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25 // Specify a optional status led by GPIO number which blinks when entering the bootloader

#define MATRIX_ROWS 2
#define MATRIX_COLS 6

#define USE_I2C TRUE
#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN GP3
//#define I2C2_SCL_PAL_MODE 3
#define I2C1_SDA_PIN GP2
//#define I2C2_SDA_PAL_MODE 3

#undef F_SCL
#define F_SCL 1000000

#ifdef CONSOLE_ENABLE
#define DEBUG_MATRIX_SCAN_RATE
#endif