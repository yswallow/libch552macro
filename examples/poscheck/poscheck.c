#include <stdio.h>
#include "libch552macro.h"

int main(void) {
    libusb_device_handle *dev;
    dev = ch552macro_init();
    
    if( dev==NULL ) {
        printf("opening device fail\n");
        return -1;
    }
    
    printf("CH552 macropad open\n");
    
    // 1 to 9
    for(uint8_t id=1; id<10; id++) {
        ch552macro_set_key(dev, id, 0x00, 0x1D+id);
    }
    // a to z
    for(uint8_t id=10; id<10+26; id++) {
        ch552macro_set_key(dev, id, 0x00, id-6);
    }
    
    // A to Z
    for(uint8_t id=10+26; id<10+26+26; id++) {
        ch552macro_set_key(dev, id, 0x02, id-32);
    }
    
    printf("finish\n");
    ch552macro_deinit(dev);
    
    return 0;
}
