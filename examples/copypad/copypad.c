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
    
    ch552macro_set_key(dev, 1, 0x01, 0x04); // C-A
    ch552macro_set_key(dev, 2, 0x01, 0x06); // C-C
    ch552macro_set_key(dev, 3, 0x01, 0x19); // C-V
    
    ch552macro_set_key(dev, 0x0D, 0x01, 0x1D); // C-Z
    ch552macro_set_key(dev, 0x0E, 0x00, 0x2A); // Del
    ch552macro_set_key(dev, 0x0F, 0x03, 0x1D); // C-S-Z
    
    printf("exit\n");
    ch552macro_deinit(dev);
    
    return 0;
}
