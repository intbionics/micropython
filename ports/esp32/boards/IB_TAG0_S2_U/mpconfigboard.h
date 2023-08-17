
#define MICROPY_HW_BOARD_NAME "IB_TAG0_S2_U"
#define MICROPY_HW_MCU_NAME "ESP32-S2"

#define MICROPY_PY_BLUETOOTH                (0)
#define MICROPY_HW_ENABLE_SDCARD            (0)

#define MICROPY_HW_I2C0_SCL (9)
#define MICROPY_HW_I2C0_SDA (8)

//spi1, these pins overlap with ext spram/flash octal pins
#define MICROPY_HW_SPI1_MOSI (35)  // SDO
#define MICROPY_HW_SPI1_MISO (37)  // SDI
#define MICROPY_HW_SPI1_SCK (36)

//use spi2
#define MICROPY_HW_SPI2_MOSI (16)  // SDO
#define MICROPY_HW_SPI2_MISO (18)  // SDI
#define MICROPY_HW_SPI2_SCK (17)

//allow second dupterm
//#define MICROPY_PY_OS_DUPTERM  (2)

//DISABLE REPL WITHOUT MODIFYING machine_uart.c
//#define MICROPY_HW_UART_REPL       -1 //still giving me errors
#define MICROPY_HW_UART_REPL_BAUD  921600
