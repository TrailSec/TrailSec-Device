#include <stdio.h>
#include "views.h"
#include "../modules/images/images.h"
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

    /* Setup touch area for [CHECKIN_BUTTON] & [LOGOUT_BUTTON] */
    Box button_checkin = createBox(CHECKIN_BUTTON_POSITION_X, CHECKIN_BUTTON_POSITION_Y, CHECKIN_BUTTON_HEIGHT, CHECKIN_BUTTON_WIDTH);
    Box button_logout = createBox(LOGOUT_BUTTON_POSITION_X, LOGOUT_BUTTON_POSITION_Y, LOGOUT_BUTTON_HEIGHT, LOGOUT_BUTTON_WIDTH);

    /* Draw UI on screen */
    drawView_main();

    while(1){
        /* Listen for inputs on the touchscreen */
        if ((TOUCHSCREEN_STATUS & TOUCHSCREEN_STATUS_RX_MASK) == TOUCHSCREEN_STATUS_RX_MASK) {
            touchInput = TouchPressed();
            touchInput = TouchRelease();

            /* Check if touch input fall within the [LOGOUT_BUTTON] */
            if (isTouchInputWithinBox(touchInput, button_checkin)) {
                printf("CHECKING IN...\n");
                next_state = VIEW_CHECKIN_ID;
                break;
            }

            /* Check if touch input fall within the [LOGOUT_BUTTON] */
            if (isTouchInputWithinBox(touchInput, button_logout)) {
                next_state = VIEW_SPLASHSCREEN_ID;
                break;
            }
        }
    }

    return next_state;
}