#include "libusb.h"

#define REPORT_ID 3
#define EPNUM 2
#define REPORT_SIZE 8

static int transferred;

static uint8_t ch552_start_sequence[REPORT_SIZE] = { REPORT_ID, 0xA1, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 };
static uint8_t ch552_end_sequence[REPORT_SIZE] =  { REPORT_ID, 0xAA, 0xAA, 0x00, 0x00, 0x00, 0x00, 0x00 };
static uint8_t ch552_led_end_sequence[REPORT_SIZE] = { REPORT_ID, 0xAA, 0xA1, 0x00, 0x00, 0x00, 0x00, 0x00 };

static int ch552macro_transfer(libusb_device_handle* dev, uint8_t *report, uint8_t report_count) {
    int ret;
    ret = libusb_interrupt_transfer(dev, EPNUM, ch552_start_sequence, REPORT_SIZE, &transferred, 200);
    if( ret ) {
        return ret;
    }
    for(uint8_t i=0; i<report_count; i++) {
        ret = libusb_interrupt_transfer(dev, EPNUM, report+REPORT_SIZE*i, REPORT_SIZE, &transferred, 200);
        if( ret ) {
            return ret;
        }
    }
    ret = libusb_interrupt_transfer(dev, EPNUM, ch552_end_sequence, REPORT_SIZE, &transferred, 200);
    if( ret ) {
        return ret;
    }
    
    return 0;
}

libusb_device_handle* ch552macro_init(void) {
    libusb_device_handle *dev;
    libusb_init(NULL);
    dev = libusb_open_device_with_vid_pid(NULL, 0x1189, 0x8890);
    if( dev==NULL ) {
        libusb_exit(NULL);
    }
    return dev;
}

int ch552macro_set_key(libusb_device_handle* dev, uint8_t key_id, uint8_t modifier, uint8_t keycode) {
    uint8_t report[2][REPORT_SIZE] = {
        {REPORT_ID, key_id, 0x11, 0x01, 0x00, modifier, 0x00, 0x00},
        {REPORT_ID, key_id, 0x11, 0x01, 0x01, modifier, keycode, 0x00}
    };
    
    return ch552macro_transfer(dev, &(report[0][0]), 2);
}

int ch552macro_set_mouse(libusb_device_handle* dev, uint8_t key_id, uint8_t button, int8_t x, int8_t y, int8_t wheel, uint8_t modifier) {
    uint8_t report[REPORT_SIZE] = { 
        REPORT_ID, key_id, 0x13,
        button, x, y, wheel, modifier };
    return ch552macro_transfer(dev, report, 1);
}

int ch552macro_set_consumer(libusb_device_handle* dev, uint8_t key_id, uint16_t consumer_id) {
    uint8_t report[REPORT_SIZE] = { 
        REPORT_ID, key_id, 0x12, consumer_id&0xFF, consumer_id>>8, 0,0,0 };
    return ch552macro_transfer(dev, report, 1);
}

int ch552macro_set_led(libusb_device_handle* dev, uint8_t num) {
    uint8_t report[REPORT_SIZE] = { REPORT_ID, 0xB0, 0x18, num, 0x00, 0x00, 0x00, 0x00 };
    int ret = libusb_interrupt_transfer(dev, EPNUM, ch552_start_sequence, REPORT_SIZE, &transferred, 200);
    if(ret) {
        return ret;
    }
    
    ret = libusb_interrupt_transfer(dev, EPNUM, report, REPORT_SIZE, &transferred, 200);
    if(ret) {
        return ret;
    }
    
    ret = libusb_interrupt_transfer(dev, EPNUM, ch552_led_end_sequence, REPORT_SIZE, &transferred, 200);
    if(ret) {
        return ret;
    }
    return 0;
}

void ch552macro_deinit(libusb_device_handle* dev) {
    libusb_close(dev);
    libusb_exit(NULL);
}


