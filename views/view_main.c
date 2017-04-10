#include <stdio.h>
#include <string.h>
#include "views.h"
#include "../modules/images/images.h"
#include "../modules/bluetooth/bluetooth.h"
#include "../modules/touchscreen/touchscreen.h"

#define CHECKIN_BUTTON_POSITION_X 16 + VIEW_POSITION_X
#define CHECKIN_BUTTON_POSITION_Y 16 + VIEW_POSITION_Y
#define CHECKIN_BUTTON_HEIGHT 128
#define CHECKIN_BUTTON_WIDTH 128

#define LOGOUT_BUTTON_POSITION_X 16 + VIEW_POSITION_X
#define LOGOUT_BUTTON_POSITION_Y 150 + VIEW_POSITION_Y
#define LOGOUT_BUTTON_HEIGHT 32
#define LOGOUT_BUTTON_WIDTH 128

int 
loadView_main(){

    Point touchInput;
    int next_state;
    char BT_str_buffer[BLUETOOTH_STRING_BUFFER_SIZE];

    /* Setup touch area for [CHECKIN_BUTTON] & [LOGOUT_BUTTON] */
    Box button_checkin = createBox(CHECKIN_BUTTON_POSITION_X, CHECKIN_BUTTON_POSITION_Y, CHECKIN_BUTTON_HEIGHT, CHECKIN_BUTTON_WIDTH);
    Box button_logout = createBox(LOGOUT_BUTTON_POSITION_X, LOGOUT_BUTTON_POSITION_Y, LOGOUT_BUTTON_HEIGHT, LOGOUT_BUTTON_WIDTH);

    /* Draw UI on screen */
    drawImage_main();

    while(1){
        /* Listen for inputs on the touchscreen */
        if ((TOUCHSCREEN_STATUS & TOUCHSCREEN_STATUS_RX_MASK) == TOUCHSCREEN_STATUS_RX_MASK) {
            touchInput = TouchPressed();
            touchInput = TouchRelease();

            /* Check if touch input fall within the [LOGOUT_BUTTON] */
            if (isTouchInputWithinBox(touchInput, button_checkin)) {
                printf("[DEVICE]: CHECKING IN...\n");
                next_state = VIEW_CHECKIN_ID;
                break;
            }

            /* Check if touch input fall within the [LOGOUT_BUTTON] */
            if (isTouchInputWithinBox(touchInput, button_logout)) {
                printf("[DEVICE]: LOGGING OUT...\n");
                next_state = VIEW_SPLASHSCREEN_ID;
                break;
            }
        }

        /* Listen for commands from the bluetooth module */
        if ((BLUETOOTH_STATUS & BLUETOOTH_STATUS_RX_MASK) == BLUETOOTH_STATUS_RX_MASK) {
            if (BLUETOOTH_getString(BT_str_buffer, BLUETOOTH_STRING_BUFFER_SIZE) != -1) {
                printf("[BT-MODULE]: RECEIVED \"%s\"\n", BT_str_buffer);

                /* If we have a string of less than 10 chars, assume that it's a valid command */
                if (strlen(BT_str_buffer) < 10) {

                    /* CHECK-IN via Blueooth */
                    if (strcmp("checkin", BT_str_buffer) == 0 || 
                        strcmp("check in", BT_str_buffer) == 0 || 
                        strcmp("check-in", BT_str_buffer) == 0 ||
                        strcmp("chicken", BT_str_buffer) == 0 ||
                        strcmp("trek", BT_str_buffer) == 0 ||
                        strcmp("track", BT_str_buffer) == 0 ||
                        strcmp("truck", BT_str_buffer) == 0) {
                        printf("[DEVICE]: CHECKING IN...\n");
                        next_state = VIEW_CHECKIN_ID;
                        break;
                    }

                    /* LOG OUT via Blueooth */
                    if (strcmp("logout", BT_str_buffer) == 0 || 
                        strcmp("log out", BT_str_buffer) == 0 ||
                        strcmp("Q", BT_str_buffer) == 0 ||
                        strcmp("q", BT_str_buffer) == 0) {
                        printf("[DEVICE]: LOGGING OUT...\n");
                        next_state = VIEW_SPLASHSCREEN_ID;
                        break;
                    }
                }
            }
        }
    }

    return next_state;
}