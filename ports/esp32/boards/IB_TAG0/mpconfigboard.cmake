set(IDF_TARGET esp32s3)

set(SDKCONFIG_DEFAULTS
    boards/sdkconfig.base
    boards/sdkconfig.usb
    boards/sdkconfig.ble
    boards/sdkconfig.240mhz
    boards/sdkconfig.spiram_sx
    boards/IB_TAG0/sdkconfig.board
)
if(NOT MICROPY_FROZEN_MANIFEST)
    set(MICROPY_FROZEN_MANIFEST ${MICROPY_BOARD_DIR}/manifest.py)
endif()

#set(MICROPY_CROSS_FLAGS "-march=xtensawin -X emit=native")


