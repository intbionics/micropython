/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2021 Damien P. George
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "py/runtime.h"
#include "py/mphal.h"
#include "usb.h"

#if MICROPY_HW_USB_CDC
#include "esp_rom_gpio.h"
#include "esp_mac.h"
#include "esp_private/usb_phy.h"

#include "shared/tinyusb/mp_usbd.h"

static usb_phy_handle_t phy_hdl;


void usb_init(void) {
// <<<<<<< HEAD
    // ref: https://github.com/espressif/esp-usb/blob/4b6a798d0bed444fff48147c8dcdbbd038e92892/device/esp_tinyusb/tinyusb.c
// =======
    // Initialise the USB with defaults.
    // tinyusb_config_t tusb_cfg = {0};
   
	// ssmith
	// we want to supply a unique serial number for every device, supply a custom descriptor
	//example: managed_components/espressif__esp_tinyusb/usb_descriptors.c
 
    uint8_t chipid[6];
    esp_efuse_mac_get_default(chipid);
	static char serial[16]; // needs to be static for persistence
	sprintf(serial, "%02x%02x%02x%02x%02x%02x", chipid[5], chipid[4], chipid[3], chipid[2], chipid[1], chipid[0]);

    tusb_desc_strarray_device_t descriptor_str = {
        // array of pointer to string descriptors
        (char[]){0x09, 0x04},                // 0: is supported language is English (0x0409)
        CONFIG_TINYUSB_DESC_MANUFACTURER_STRING, // 1: Manufacturer
        CONFIG_TINYUSB_DESC_PRODUCT_STRING,      // 2: Product
		serial,   // 3: Serials, should use chip ID
		#if CONFIG_TINYUSB_CDC_ENABLED
    		CONFIG_TINYUSB_DESC_CDC_STRING,          // 4: CDC Interface
		#else
    		"",
		#endif

		#if CONFIG_TINYUSB_MSC_ENABLED
    		CONFIG_TINYUSB_DESC_MSC_STRING,          // 5: MSC Interface
		#else
    		"",
		#endif
    };
	// sprintf(descriptor_str[3], "%02x%02x%02x%02x%02x%02x", chipid[5], chipid[4], chipid[3], chipid[2], chipid[1], chipid[0]);
	// sprintf(descriptor_str[3], "test");

    tinyusb_config_t tusb_cfg = {
        .device_descriptor = NULL,  // Use default device descriptor specified in Menuconfig
        .string_descriptor = descriptor_str,
        .external_phy = false,      // Use internal USB PHY
        .configuration_descriptor = NULL
    };

    ESP_ERROR_CHECK(tinyusb_driver_install(&tusb_cfg));
// >>>>>>> c4ef4ad88 (re-sync with micropython master, copied over changes from old version, IB_GPS0 compiling and running)

    // Configure USB PHY
    usb_phy_config_t phy_conf = {
        .controller = USB_PHY_CTRL_OTG,
        .otg_mode = USB_OTG_MODE_DEVICE,
    };
    // Internal USB PHY
    phy_conf.target = USB_PHY_TARGET_INT;

    // Init ESP USB Phy
    usb_new_phy(&phy_conf, &phy_hdl);

    // Init MicroPython / TinyUSB
    mp_usbd_init();

}

#if CONFIG_IDF_TARGET_ESP32S3
void usb_usj_mode(void) {
    // Switch the USB PHY back to Serial/Jtag mode, disabling OTG support
    // This should be run before jumping to bootloader.
    usb_del_phy(phy_hdl);
    usb_phy_config_t phy_conf = {
        .controller = USB_PHY_CTRL_SERIAL_JTAG,
    };
    usb_new_phy(&phy_conf, &phy_hdl);
}
#endif

void mp_usbd_port_get_serial_number(char *serial_buf) {
    // use factory default MAC as serial ID
    uint8_t mac[8];
    esp_efuse_mac_get_default(mac);
    MP_STATIC_ASSERT(sizeof(mac) * 2 <= MICROPY_HW_USB_DESC_STR_MAX);
    mp_usbd_hex_str(serial_buf, mac, sizeof(mac));
}

#endif // MICROPY_HW_USB_CDC
