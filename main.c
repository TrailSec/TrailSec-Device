#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lib/Colours.h"
#include "lib/gps.h"
#include "lib/OutGraphicsCharFont.h"
#include "lib/touchscreen.h"
#include "lib/wifi.h"

int main() {

	printf("Initializing GPS...\n");
	Init_Touch();
	printf("Initializing Touch Screen...\n");
	init_gps();
	printf("Initializing Wifi...\n");
	init_wifi();

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
