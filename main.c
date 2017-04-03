#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "modules/graphics/Colours.h"
#include "modules/graphics/graphics.h"
#include "modules/graphics/OutGraphicsCharFont.h"
#include "modules/touchscreen/touchscreen.h"
#include "modules/wifi/wifi.h"
#include "modules/gps/gps.h"
#include "modules/bluetooth/bluetooth.h"
#include "modules/images/watchframe.h"
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
    // configure_bluetooth_dongle(); // Setup id & pin for bluetooth module
    printf("Done!\n");

    // drawIntroScreen();
    // ClearScreen(GREEN);
    drawWatchframe(250, 0);

//-----------------------------------------------
    // int i;
    // for (i=0; i<100; i++) {
    //  WriteAPixel(100, i, WHITE);
    //  WriteAPixel(101, i, WHITE);
    //  WriteAPixel(102, i, WHITE);
    //  WriteAPixel(103, i, WHITE);
    //  WriteAPixel(104, i, WHITE);
    // }/
//-----------------------------------------------
    char str_buffer[BLUETOOTH_STRING_BUFFER_SIZE];
    while(1){
        // ClearScreen(WHITE);
        // int userId = 0;
        // drawMainScreen(userId);
        // mainScreenFunctionality();

        if ((BLUETOOTH_STATUS & BLUETOOTH_STATUS_RX_MASK) == BLUETOOTH_STATUS_RX_MASK) {
            // char temp = getchar_bluetooth();
            // printf("%c", temp);
            // printf("^\n");
            if (getCommand_bluetooth(str_buffer, BLUETOOTH_STRING_BUFFER_SIZE) != -1) {
                printf(">>>%s", str_buffer);
                printf("<<< DONE\n");
            }
            // printf("v\n");
        }

        if ((TOUCHSCREEN_STATUS & TOUCHSCREEN_STATUS_RX_MASK) == TOUCHSCREEN_STATUS_RX_MASK) {
            Point temp;
            temp = TouchPressed();
            temp = TouchRelease();
            printf("%d, %d\n", temp.x, temp.y);
        }
    }
//-----------------------------------------------

    printf("Done!!!\n");

    return 0;
}
