#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "modules/graphics/graphics.h"
#include "modules/touchscreen/touchscreen.h"
#include "modules/wifi/wifi.h"
#include "modules/gps/gps.h"
#include "modules/bluetooth/bluetooth.h"
#include "modules/images/images.h"
#include "views/views.h"

int main() {

    printf("Initializing GPS Module... ");
    Init_Touch();
    printf("Done!\n");

    printf("Initializing Touch Screen Module... ");
    init_gps();
    printf("Done!\n");

    printf("Initializing Wifi Module... ");
    init_wifi();
    printf("Done!\n");

    printf("Initializing Bluetooth Module... ");
    init_bluetooth();
    /* Setup id & pin for bluetooth module */
    // configure_bluetooth_dongle();
    printf("Done!\n");

    /* Draw watchframe on LCD display */
    drawWatchframe();

    /* */
    int VIEW_STATE = 0;
    while(1){
        VIEW_STATE = loadView(VIEW_STATE);
    }

    return 0;
}
