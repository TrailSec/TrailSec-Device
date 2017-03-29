#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "gps.h"
#include "touchscreen.h"
#include "graphics.h"
#include "OutGraphicsCharFont.h"

void Init_Touch(void) {
	Touch_Control = 0x15;
	Touch_Baud = 0x05;
}

void WaitingForTouch(void){
	while (TouchScreen_RX != 0x80){}
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
	while ((Touch_Status & 0x02) != 0x02){}
	TouchScreen_TX = character & 0xFF;
	return TouchScreen_TX;
}

int outputTouchScreenChar(void) {
	while ((Touch_Status & 0x01) != 0x01){}
	return  TouchScreen_RX;
}
