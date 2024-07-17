#pragma once

#define RP2040_MCUCONF TRUE

#undef RP_I2C_USE_I2C0
#define RP_I2C_USE_I2C0 FALSE

#undef RP_I2C_USE_I2C1
#define RP_I2C_USE_I2C1 TRUE

/*#undef RP_IRQ_USB0_PRIORITY
#define RP_IRQ_USB0_PRIORITY 0

#undef RP_SIO_USE_UART0
#define RP_SIO_USE_UART0 TRUE

#define UART_DRIVER SD0
#define UART_TX_PIN GP0
#define UART_RX_PIN GP1

#define PLATFORM_USB_USE_USB1 TRUE
#undef MIDI_ENABLE
#undef CONSOLE_ENABLE
#undef MOUSE_ENABLE
#include <hal_usb_lld.h>
#include <hal_usb.h>*/
#define PLATFORM_USB_USE_USB1 TRUE
#define PLATFORM_USB_USE_USB0 TRUE
#define HAL_USE_USB TRUE
#define RP_USB_USE_USBD0 TRUE
#define RP_USB_USE_USBD1 TRUE
//#define USB_DRIVER USBD0
#define RP_IRQ_USB0_PRIORITY 3
#define RP_IRQ_UART0_PRIORITY 0
#define RP_IRQ_UART1_PRIORITY 1
#define RP_IRQ_I2C1_PRIORITY 2
//#include <hal_usb_lld.h>
//#include "lib\chibios-contrib\os\hal\ports\RP\LLD\USBDv1\hal_usb_lld.h"