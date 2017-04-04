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
    init_gps();
    printf("Done!\n");

    printf("Initializing Wifi Module... ");
    init_wifi();
    printf("Done!\n");

    /* Setup id & pin for bluetooth module */
    // configure_bluetooth_dongle();
    printf("Initializing Bluetooth Module... ");
    init_bluetooth();
    printf("Done!\n");

    printf("Initializing Memory for User Session... ");
    CURRENT_USER_ID = malloc(sizeof(char) * 50);
    int i;
    char temp[] = "TESTlOXmUqhwrdduuDrLqacuvSI3";
    for (i = 0; temp[i] != '\0'; i++)
        CURRENT_USER_ID[i] = temp[i];
    CURRENT_USER_ID[i] = '\0';
    printf("Done!\n");

    /* Clear LCD display (WHITE) & draw watchframe */
    ProgramPalette(63, 0xFFFFFF);
    ClearScreen(63);
    drawWatchframe();

    /* Start loading UI views within the watchframe */
    int VIEW_STATE = 0;
    while(1){
        VIEW_STATE = loadView(VIEW_STATE);
    }

    free(CURRENT_USER_ID);

    return 0;
}
