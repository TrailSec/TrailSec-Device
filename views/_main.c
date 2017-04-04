#include "views.h"
#include "../modules/images/images.h"
#include "../modules/touchscreen/touchscreen.h"

int 
loadView_main(){

    Point touchInput;
    Box button_continue;
    int next_state;

    /* Draw UI on screen */
    drawView_main();

    /* Setup touch area for [CONTINUE_BUTTON] */
    button_continue.x = VIEW_POSITION_X;
    button_continue.y = VIEW_POSITION_Y;
    button_continue.width = VIEW_POSITION_X + VIEW_WIDTH;
    button_continue.height = VIEW_POSITION_Y + VIEW_HEIGHT;

    /* Listen for inputs on the touchscreen */
    while(1){
        if ((TOUCHSCREEN_STATUS & TOUCHSCREEN_STATUS_RX_MASK) == TOUCHSCREEN_STATUS_RX_MASK) {
            touchInput = TouchPressed();
            touchInput = TouchRelease();

            /* Check if touch input fall within the [CONTINUE_BUTTON] */
            if (isTouchInputWithinBox(touchInput, button_continue)) {
                next_state = VIEW_SPLASHSCREEN_ID;
                break;
            }
        }
    }

    return next_state;
}