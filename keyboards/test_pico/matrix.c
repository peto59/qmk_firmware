#include <stdint.h>
#include <stdbool.h>
#include <i2c_master.h>
#include "print.h"
#include "debug.h"
#include "debounce.h"
#include "quantum.h"
#include "matrix.h"

#include QMK_KEYBOARD_H

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }
__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }
__attribute__((weak)) void matrix_init_user(void) {}
__attribute__((weak)) void matrix_scan_user(void) {}
__attribute__((weak)) void matrix_init_quantum(void) { matrix_init_kb(); }
__attribute__((weak)) void matrix_scan_quantum(void) { matrix_scan_kb(); }

uint_fast8_t col_pins [MAIN_COLS] = {GP14, GP17};
uint_fast8_t row_pins [MAIN_ROWS] = {GP15, GP16};

static matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
static matrix_row_t matrix[MATRIX_ROWS];      // debounced values

inline uint8_t matrix_rows(void) { return MATRIX_ROWS; }
inline uint8_t matrix_cols(void) { return MATRIX_COLS; }


matrix_row_t matrix_get_row(uint8_t row) {
    // TODO: return the requested row data
    return matrix[row];
}

void matrix_print(void) {
#ifdef CONSOLE_ENABLE
	for (uint_fast8_t r = 0; r < MATRIX_ROWS; r++) {
		dprintf("%u\n", matrix[r]);
	}
#endif
}

void matrix_init(void) {
    // TODO: initialize hardware and global matrix state here
    i2c_initialize();
    for(uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i] = 0;
    }
	
	for (uint8_t i = 0; i < MAIN_ROWS; i++) {
        gpio_set_pin_input_low(row_pins[i]);
    }

    for (uint8_t i = 0; i < MAIN_COLS; i++) {
        gpio_set_pin_output(col_pins[i]);
    }
   
    // Unless hardware debouncing - Init the configured debounce routine
    //debounce_init(MATRIX_ROWS);

    // This *must* be called for correct keyboard behavior
	matrix_init_kb();
    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
    
    bool changed = false;
    matrix_row_t current_matrix[MATRIX_ROWS];
	uint_fast8_t r;
	for (r = 0; r < MATRIX_ROWS; r++) {
		current_matrix[r] = 0;
	}
	
	for (uint_fast8_t c = 0; c < MAIN_COLS; c++) {
		gpio_write_pin_high(col_pins[c]);
		wait_us(1);
		for (r = 0; r < MAIN_ROWS; r++) {
			current_matrix[r] |= (gpio_read_pin(row_pins[r]) << (c+RIGHT_COLS));
		}
		gpio_write_pin_low(col_pins[c]);
	}
		
	uint8_t read;
	i2c_status_t status;
	for (r = 0; r < MATRIX_ROWS; r++) {
		status = i2c_read_register(SLAVE_I2C_ADDRESS_RIGHT, r, &read, 1, 1);
		if(status == I2C_STATUS_SUCCESS){	
			current_matrix[r] |= read;
		}
#ifdef CONSOLE_ENABLE
		else
		{
			dprint("i2c error right\n");
		}
#endif
		
		status = i2c_read_register(SLAVE_I2C_ADDRESS_LEFT, r, &read, 1, 1);
		if(status == I2C_STATUS_SUCCESS){	
			current_matrix[r] |= (read << (MAIN_COLS+RIGHT_COLS));
		}
#ifdef CONSOLE_ENABLE
		else
		{
			dprint("i2c error left\n");
		}
#endif
		
		if(current_matrix[r] != matrix[r]) {
            matrix[r] = current_matrix[r];
            changed = true;
        } 
	}

    //debounce(raw_matrix, matrix, MATRIX_ROWS, changed);

    matrix_scan_quantum();
	matrix_scan_kb();
    
    return changed;
}