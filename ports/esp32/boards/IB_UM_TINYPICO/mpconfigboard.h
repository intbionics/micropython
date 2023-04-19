#define MICROPY_HW_BOARD_NAME "IB_UM_TINYPICO"
#define MICROPY_HW_MCU_NAME   "ESP32-UM-TINYPICO"

#define MICROPY_HW_I2C0_SCL (22)
#define MICROPY_HW_I2C0_SDA (21)

#define MICROPY_HW_SPI1_SCK (18)
#define MICROPY_HW_SPI1_MOSI (23)
#define MICROPY_HW_SPI1_MISO (19)

//GATTC write limited to 20 bytes without increase, 
//despite mtu exhcange
//https://github.com/micropython/micropython/issues/8258
//#define MP_BLUETOOTH_DEFAULT_ATTR_LEN (4096)


#define MICROPY_WRAP_MP_BINARY_OP (0)

//DISABLE REPL WITHOUT MODIFYING machine_uart.c
//#define MICROPY_HW_UART_REPL       -1 //still giving me errors
#define MICROPY_HW_UART_REPL_BAUD  921600
