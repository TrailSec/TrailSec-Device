#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lib/Colours.h"

int main() {

	printf("Initializing GPS...\n");
	Init_Touch();
	printf("Initializing Touch Screen...\n");
	init_gps();
	printf("Initializing Wifi...\n");
	init_wifi();

	drawIntroScreen();
	ClearScreen(WHITE);
	char userPrompt[] = "Please enter UserId!";
	displayPopup(userPrompt, 20, LIME);

	while(1){
		ClearScreen(WHITE);
		drawLoginScreen();
		int userId = loginVerification();
		drawMainScreen(userId);
		mainScreenFunctionality();
		printf("Done!!!\n");
	}

	return 0;
}
