
#define MICROPY_HW_BOARD_NAME "IB_TAG0"
#define MICROPY_HW_MCU_NAME   "ESP32-S3"

#define MICROPY_PY_MACHINE_DAC              (0)

#define MICROPY_HW_I2C0_SCL                 (9)
#define MICROPY_HW_I2C0_SDA                 (8)

//spi1, these pins overlap with ext spram/flash octal pins
#define MICROPY_HW_SPI1_MOSI (35)
#define MICROPY_HW_SPI1_SCK (36)
#define MICROPY_HW_SPI1_MISO (37)

#define MICROPY_HW_SPI2_MOSI (11)
#define MICROPY_HW_SPI2_SCK (12)
#define MICROPY_HW_SPI2_MISO (13)

//DISABLE REPL WITHOUT MODIFYING machine_uart.c
//#define MICROPY_HW_UART_REPL       -1 //still giving me errors
#define MICROPY_HW_UART_REPL_BAUD  921600

