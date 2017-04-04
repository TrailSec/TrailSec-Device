#include <stdio.h>
#include "../modules/images/images.h"
#include "views.h"

int
loadView(int view_state) {
    int next_state;

    switch (view_state) {
        case VIEW_SPLASHSCREEN_ID:
            next_state = loadView_splashscreen();
            break;
        case VIEW_BLUETOOTHPAIRING_ID:
            next_state = loadView_bluetoothPairing();
            break;
        case VIEW_MAIN_ID:
            next_state = loadView_main();
            break;
        case VIEW_CHECKIN_ID:
            next_state = loadView_checkIn();
            break;
        default:
            printf("ERROR: INVALID STATE!\n");
            break;
    }

    return next_state;
}

