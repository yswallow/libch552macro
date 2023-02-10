#include "libusb.h"

libusb_device_handle* ch552macro_init(void);
int ch552macro_set_key     (libusb_device_handle* dev, uint8_t key_id, uint8_t modifier, uint8_t keycode);
int ch552macro_set_mouse   (libusb_device_handle* dev, uint8_t key_id, uint8_t button, int8_t x, int8_t y, int8_t wheel, uint8_t modifier);
int ch552macro_set_consumer(libusb_device_handle* dev, uint8_t key_id, uint16_t consumer_id);
int ch552macro_set_led     (libusb_device_handle* dev, uint8_t num);
void ch552macro_deinit     (libusb_device_handle* dev);

