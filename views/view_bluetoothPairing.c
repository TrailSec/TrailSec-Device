#include <string.h>
#include "views.h"
#include "../modules/images/images.h"
#include "../modules/bluetooth/bluetooth.h"
#include "../modules/touchscreen/touchscreen.h"

extern char *CURRENT_USER_ID;

int 
loadView_bluetoothPairing(){

    int next_state = VIEW_MAIN_ID;
    char BT_str_buffer[BLUETOOTH_STRING_BUFFER_SIZE];

    /* Draw UI on screen */
    drawView_bluetoothPairing();

    /* Listen for commands from the bluetooth module */
    while(1){
        if ((BLUETOOTH_STATUS & BLUETOOTH_STATUS_RX_MASK) == BLUETOOTH_STATUS_RX_MASK) {
            if (BLUETOOTH_getString(BT_str_buffer, BLUETOOTH_STRING_BUFFER_SIZE) != -1) {
                printf("[BT-MODULE]: RECEIVED \"%s\"\n", BT_str_buffer);

                /* 
                 * If we have a string of greater than 20 chars, assume that it's the user-id
                 *  - Set the received user-id into our global variable CURRENT_USER_ID
                 */
                if (strlen(BT_str_buffer) > 20) {
                    int i;
                    for (i = 0; BT_str_buffer[i] != '\0'; i++)
                        CURRENT_USER_ID[i] = BT_str_buffer[i];
                    CURRENT_USER_ID[i] = '\0';
                    printf("[BT-MODULE]: VALID USER-ID, LOGGING IN...\n", CURRENT_USER_ID);
                    break;
                }
            }
        }
    }

    return next_state;
}