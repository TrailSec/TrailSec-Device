#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lib/Colours.h"
#include "lib/gps.h"
#include "lib/OutGraphicsCharFont.h"
#include "lib/touchscreen.h"
#include "lib/wifi.h"
#include "lib/bluetooth.h"

int main() {

	printf("Initializing GPS Module... ");
	Init_Touch();
	printf("Done!\n");

	printf("Initializing Touch Screen Module... ");
	init_gps();
	printf("Done!\n");

	printf("Initializing Wifi Module... ");
	init_wifi();
	printf("Done!\n");

	printf("Initializing Bluetooth Module... ");
	init_bluetooth();
	configure_bluetooth_dongle();
	printf("Done!\n");

	drawIntroScreen();
	ClearScreen(WHITE);

	while(1){
		ClearScreen(WHITE);
		int userId = 0;
		drawMainScreen(userId);
		mainScreenFunctionality();
		printf("Done!!!\n");
	}

	return 0;
}
