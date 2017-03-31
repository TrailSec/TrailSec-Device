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

    drawIntroScreen();
    ClearScreen(GREEN);

    int palette[] = {15920605,15779662,15580482,15456160,15051055,14399332,14199623,14013909,13092807,12171705,12094770,11640168,10987431,10066329,8882055,13732894,7829367,5592405,4275517,2235676,1381653,197379,16711422,15985357,15382074,15132390,14992500,14720549,14594106,14329394,14201931,14129190,13733408,12958370,12566720,12501183,10789011,8420989,8355968,8290431,6710886,6315614,15455126,4605510,4276287,4145215,3552822,2631720};

    int k=0;
    for (k=0; k<8; k++){
        ProgramPalette(k, palette[k]);
    }

    int *picture = getWatchframePixelArray();
    int i=0;
    int row = 588;
    int column = 981;
    int x_offset = 200;
    int y_offset = 0;
    for (i=0; i<(row*column); i++) {
        int colorIndex = 0;
        for(colorIndex=0; colorIndex<48; colorIndex++) {
            if (palette[colorIndex] == picture[i])
                break;
        }
        if(colorIndex>=48){
            printf("FAIL\n");
            break;
        }
        WriteAPixel(x_offset+(i % row), y_offset+(i / 981), colorIndex);
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
