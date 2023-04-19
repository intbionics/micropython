


#using UART and external USB IC
esptool.py -p /dev/ttyUSB0 erase_flash
esptool.py --chip esp32s3 --port /dev/ttyUSB0 --baud 921600 write_flash -z 0 /home/ssmith/micropython/ports/esp32/build-IB_S3/firmware.bin
python -m serial.tools.miniterm  /dev/ttyUSB0 921600

#using built in USB
esptool.py --chip esp32s3 --port /dev/ttyACM0 erase_flash
esptool.py --chip esp32s3 --port /dev/ttyACM0 write_flash -z 0 /home/ssmith/micropython/ports/esp32/build-IB_S3/firmware.bin

