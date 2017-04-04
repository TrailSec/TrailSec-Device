#include "views.h"
#include "../modules/images/images.h"
#include "../modules/touchscreen/touchscreen.h"

#define CONTINUE_BUTTON_POSITION_X VIEW_POSITION_X
#define CONTINUE_BUTTON_POSITION_Y VIEW_POSITION_Y
#define CONTINUE_BUTTON_HEIGHT VIEW_WIDTH
#define CONTINUE_BUTTON_WIDTH VIEW_HEIGHT

int
loadView_splashscreen(){

    Point touchInput;
    int next_state;

    /* Setup touch area for [CONTINUE_BUTTON] */
    Box button_continue = createBox(CONTINUE_BUTTON_POSITION_X, CONTINUE_BUTTON_POSITION_Y, CONTINUE_BUTTON_HEIGHT, CONTINUE_BUTTON_WIDTH);

    /* Draw UI on screen */
    drawView_splashscreen();

    /* Listen for inputs on the touchscreen */
    while(1){
        if ((TOUCHSCREEN_STATUS & TOUCHSCREEN_STATUS_RX_MASK) == TOUCHSCREEN_STATUS_RX_MASK) {
            touchInput = TouchPressed();
            touchInput = TouchRelease();

            /* Check if touch input fall within the [CONTINUE_BUTTON] */
            if (isTouchInputWithinBox(touchInput, button_continue)) {
                next_state = VIEW_BLUETOOTHPAIRING_ID;
                break;
            }
        }
    }

    return next_state;
};