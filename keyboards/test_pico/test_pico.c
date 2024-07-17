#include "test_pico.h"

//static i2c_status_t last_err = 0;
bool i2c_initialized = false;

void i2c_initialize(void){
     
    if(!i2c_initialized) {
        i2c_init();
        i2c_initialized = true;
        
    }
    
}

bool isI2C_initialized() {
    return i2c_initialized;
}