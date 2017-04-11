#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "touchscreen.h"

void TOUCH_init(void) {
    TOUCHSCREEN_CONTROL = 0x15;
    TOUCHSCREEN_BAUD = 0x05;
}

void TOUCH_waitForTouchEvent(void){
    while (TOUCHSCREEN_RXDATA != 0x80);
}

Point TOUCH_getTouchCoordinates(int PorR){
    Point p;

    char buffer[4];
    int size = 4;
    int index;
    for (index = 0; index < size; index++) {
        buffer[index] = TOUCH_getChar();
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

Point TOUCH_onTouch(void) {
    TOUCH_waitForTouchEvent();
    return TOUCH_getTouchCoordinates(0);
}

Point TOUCH_onRelease(void) {
    TOUCH_waitForTouchEvent();
    return TOUCH_getTouchCoordinates(1);
}

int TOUCH_putChar(char c) {
    while ((TOUCHSCREEN_STATUS & TOUCHSCREEN_STATUS_TX_MASK) != TOUCHSCREEN_STATUS_TX_MASK);
    TOUCHSCREEN_TXDATA = c & 0xFF;
    return TOUCHSCREEN_TXDATA;
}

char TOUCH_getChar(void) {
    while ((TOUCHSCREEN_STATUS & TOUCHSCREEN_STATUS_RX_MASK) != TOUCHSCREEN_STATUS_RX_MASK);
    return  TOUCHSCREEN_RXDATA;
}

bool TOUCH_isPointInsideBox(Point touchInput, Box touchArea) {
    if ((touchInput.x >= touchArea.x && touchInput.x <= (touchArea.x + touchArea.width)) &&
        (touchInput.y >= touchArea.y && touchInput.y <= (touchArea.y + touchArea.height))) {
        return true;
    }
    else {
        return false;
    }
}

Box TOUCH_createBox(int x, int y, int height, int width) {
    Box thisBox;
    thisBox.x = x;
    thisBox.y = y;
    thisBox.width = width;
    thisBox.height = height;
    return thisBox;
}
