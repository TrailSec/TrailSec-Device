#include <unistd.h>
#include "views.h"
#include "../modules/images/images.h"
#include "../modules/touchscreen/touchscreen.h"

#define SPLASHSCREEN_DELAY 2 * 1000 * 1000 // 4 second

int
loadView_splashscreen(){

    Point touchInput;
    int next_state = VIEW_BLUETOOTHPAIRING_ID;

    /* Draw UI on screen */
    drawView_splashscreen();

    /* Wait for 1s before switching to the new view */
    usleep(SPLASHSCREEN_DELAY);

    return next_state;
};