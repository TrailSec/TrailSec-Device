#include <stdio.h>
#include <string.h>
#include "views.h"
#include "../modules/images/images.h"
#include "../modules/gps/gps.h"
#include "../modules/wifi/wifi.h"
#include "../modules/touchscreen/touchscreen.h"

#define CONTINUE_BUTTON_POSITION_X VIEW_POSITION_X
#define CONTINUE_BUTTON_POSITION_Y VIEW_POSITION_Y
#define CONTINUE_BUTTON_HEIGHT VIEW_WIDTH
#define CONTINUE_BUTTON_WIDTH VIEW_HEIGHT

extern char *CURRENT_USER_ID;

int
loadView_checkIn(){

    int next_state = VIEW_MAIN_ID;

    /* Draw UI on screen */
    drawView_checkIn();

    /* Get current position from GPS Module */
    double latitude, longitude;
    GPS_getCoordinates(&latitude, &longitude);

    /* Make POST request to Firebase REST API via Wifi Module */
    char str_latitude[50], str_longitude[50];
    sprintf(str_latitude,"%.5f", latitude);
    sprintf(str_longitude, "%.5f", longitude);
    WIFI_sendCoordinates(str_latitude, str_longitude, CURRENT_USER_ID);

    /* TRY MAKING POST REQUEST w/ READ GPS MODULE */
    // WIFI_sendCoordinates("49.2765", "-123.2177", "HsrdlOXmUqhwrdduuDrLqacuvSI3");
    // WIFI_sendCoordinates("49.2765", "-123.2177", CURRENT_USER_ID);

    return next_state;
};