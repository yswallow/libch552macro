#include <stdio.h>
#include "libch552macro.h"

int main(int argc, char* argv[]) {
    libusb_device_handle *dev;
    dev = ch552macro_init();
    
    if( dev==NULL ) {
        printf("opening device fail\n");
        return -1;
    }
    
    printf("CH552 macropad open\n");
    ch552macro_set_led(dev, argv[argc-1][0]-'0');
    
    printf("finish\n");
    ch552macro_deinit(dev);
    
    return 0;
}
