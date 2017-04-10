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

char *CURRENT_USER_ID;

int main() {

    printf("Initializing GPS Module... ");
    Init_Touch();
    printf("Done!\n");

    printf("Initializing Touch Screen Module... ");
    GPS_init();
    printf("Done!\n");

    printf("Initializing Wifi Module... ");
    init_wifi();
    printf("Done!\n");

    /* Setup id & pin for bluetooth module */
    // BLUETOOTH_configureModule();
    printf("Initializing Bluetooth Module... ");
    BLUETOOTH_init();
    printf("Done!\n");

    printf("Initializing Memory for User Session... ");
    CURRENT_USER_ID = calloc(50, sizeof(char));
    printf("%s", CURRENT_USER_ID); // Should be printing an empty string...
    printf("Done!\n");

    /* Clear LCD display (WHITE) & draw watchframe */
    ProgramPalette(63, 0xFFFFFF);
    ClearScreen(63);
    drawImage_watchFrame();

    /* Start loading UI views within the watchframe */
    int VIEW_STATE = 0;
    while(1){
        VIEW_STATE = loadView(VIEW_STATE);
    }

    free(CURRENT_USER_ID);

    return 0;
}
