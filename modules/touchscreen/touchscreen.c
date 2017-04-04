#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "touchscreen.h"

void Init_Touch(void) {
    TOUCHSCREEN_CONTROL = 0x15;
    TOUCHSCREEN_BAUD = 0x05;
}

void WaitingForTouch(void){
    while (TOUCHSCREEN_RXDATA != 0x80);
}

Point getTouchCoordinates(int PorR){
    Point p;

    int buffer[4];
    int size = 4;
    int index;
    for (index = 0; index < size; index++) {
        buffer[index] = outputTouchScreenChar();
    }
    p.x = buffer[1] << 7;
    p.x = p.x | buffer[0];

    p.y = (buffer[3] << 7);
    p.y = p.y | buffer[2];

    p.x = (p.x * 799) / 4095;

    if(PorR == 0){
        p.y = ((p.y - 125) * 479);
        p.y = p.y / 3970;
    }
    else if(PorR == 1){
        p.y = ((p.y - 150) * 479);
        p.y = p.y / 3945;
    }
    return p;
}

Point TouchPressed(void) {
    WaitingForTouch();
    return getTouchCoordinates(0);
}

Point TouchRelease(void) {
    WaitingForTouch();
    return getTouchCoordinates(1);
}

int inputTouchScreenChar(int character) {
    while ((TOUCHSCREEN_STATUS & TOUCHSCREEN_STATUS_TX_MASK) != TOUCHSCREEN_STATUS_TX_MASK);
    TOUCHSCREEN_TXDATA = character & 0xFF;
    return TOUCHSCREEN_TXDATA;
}

int outputTouchScreenChar(void) {
    while ((TOUCHSCREEN_STATUS & TOUCHSCREEN_STATUS_RX_MASK) != TOUCHSCREEN_STATUS_RX_MASK);
    return  TOUCHSCREEN_RXDATA;
}

bool isTouchInputWithinBox(Point touchInput, Box touchArea) {
    if ((touchInput.x >= touchArea.x && touchInput.x <= (touchArea.x + touchArea.width)) &&
        (touchInput.y >= touchArea.y && touchInput.y <= (touchArea.y + touchArea.height))) {
        return true;
    }
    else {
        return false;
    }
}

