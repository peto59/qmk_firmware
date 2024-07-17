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

static matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
static matrix_row_t matrix[MATRIX_ROWS];      // debounced values

inline uint8_t matrix_rows(void) { return MATRIX_ROWS; }
inline uint8_t matrix_cols(void) { return MATRIX_COLS; }


matrix_row_t matrix_get_row(uint8_t row) {
    // TODO: return the requested row data
    return matrix[row];
}

void matrix_power_up() {
    print("matrix.c->matrix_power_up()");
}

void matrix_power_down() {
    print("matrix.c->matrix_power_down()");
}

void matrix_print(void) {
	print("hello matrix print");
    //print_matrix_header();

    /*for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row);
        print(": ");
        print_matrix_row(row);
        print("\n");
    }*/
}

void matrix_init(void) {
    // TODO: initialize hardware and global matrix state here
    i2c_initialize();
    for(uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i] = 0;
    }
	print("hello i2c");
   
    // Unless hardware debouncing - Init the configured debounce routine
    //debounce_init(MATRIX_ROWS);

    // This *must* be called for correct keyboard behavior
	matrix_init_kb();
    matrix_init_quantum();
}

uint8_t matrix_scan(void) {
	print("hello");
    
    bool changed = false;
    matrix_row_t current_row = 0;

	for (uint8_t c = 0; c < MATRIX_COLS; c++) {
		gpio_write_pin_high(GP14);
		for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
            // Check if the key is pressed
			uint8_t read = gpio_read_pin(GP15);
			current_row = read;
			if(matrix[r] != current_row){
				
				matrix[r] = current_row;
				changed = true;
			}
        }
		gpio_write_pin_low(GP14);
    }
	

    //debounce(raw_matrix, matrix, MATRIX_ROWS, changed);

    matrix_scan_quantum();
	matrix_scan_kb();
    
    return changed;
}