#pragma once

#include_next <mcuconf.h>

#undef RP2040_MCUCONF
#define RP2040_MCUCONF TRUE

#undef RP_I2C_USE_I2C1
#define RP_I2C_USE_I2C1 TRUE