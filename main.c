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

    char str_buffer[BLUETOOTH_STRING_BUFFER_SIZE];
    while(1){

        /* Listen for commands from the bluetooth module */
        if ((BLUETOOTH_STATUS & BLUETOOTH_STATUS_RX_MASK) == BLUETOOTH_STATUS_RX_MASK) {
            if (getCommand_bluetooth(str_buffer, BLUETOOTH_STRING_BUFFER_SIZE) != -1) {
                printf(">>%s", str_buffer);
                printf("<<\n");
            }
        }

        /* Listen for inputs from the touchscreen controller module */
        if ((TOUCHSCREEN_STATUS & TOUCHSCREEN_STATUS_RX_MASK) == TOUCHSCREEN_STATUS_RX_MASK) {
            Point temp;
            temp = TouchPressed();
            temp = TouchRelease();
            printf("%d, %d\n", temp.x, temp.y);
        }
    }

    return 0;
}
