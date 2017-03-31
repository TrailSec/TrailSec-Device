#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lib/Colours.h"
#include "lib/touchscreen.h"
#include "lib/graphics.h"
#include "lib/OutGraphicsCharFont.h"
#include "lib/wifi.h"
#include "lib/gps.h"
#include "lib/bluetooth.h"
#include "views/views.h"
#include "images/watchframe.h"

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

    int palette[] = {15329769,12171705,10461600,9013641,3618615,2697513,2367264,1513239,197379,16711422,14672095,14079702,13027014,12566720,11053224,10461343,10132122,7631988,6710886,6315614,6250591,5789784,4473924,4275773,4210751,4145216,2235419};

    int k=0;
    for (k=0; k<48; k++){
        ProgramPalette(k, palette[k]);
    }

    ClearScreen(9);

    int *picture = getWatchframePixelArray();
    int i=0;
    int row = 300;
    int column = 500;
    int x_offset = 100;
    int y_offset = 0;
    for (i=0; i<(row*column); i++) {
        if (picture[i] == 16711422)
            continue;
        // find color
        int colorIndex = 0;
        for(colorIndex=0; colorIndex<48; colorIndex++) {
            if (palette[colorIndex] == picture[i])
                break;
        }
        if(colorIndex>=48){
            printf("FAIL\n");
            break;
        }
        else
            WriteAPixel(x_offset+(i % row), y_offset+(i / row), colorIndex);
    }

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
    // // char str_buffer[10];
    // while(1){
    //  // ClearScreen(WHITE);
    //  // int userId = 0;
    //  // drawMainScreen(userId);
    //  // mainScreenFunctionality();
    //  //
    //  // if ((BLUETOOTH_STATUS & 0x01) == 0x01) {
    //  //  if (getCommand_bluetooth(str_buffer, 9) != -1) {
    //  //      printf(">>> %s", str_buffer);
    //  //  }
    //  // }
    //  char temp = getchar_bluetooth();
    //   printf("%c", temp);
    // }
//-----------------------------------------------

    printf("Done!!!\n");

    return 0;
}
