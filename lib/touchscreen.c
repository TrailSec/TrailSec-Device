#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gps.h"
#include "touchscreen.h"

void WriteAPixel(int x, int y, int Colour) {
	WAIT_FOR_GRAPHICS; // is graphics ready for new command
	GraphicsX1Reg = x; // write coords to x1, y1
	GraphicsY1Reg = y;
	GraphicsColourReg = Colour; // set pixel colour
	GraphicsCommandReg = PutAPixel; // give graphics "write pixel" command
}
/*********************************************************************************************
 * This function read a single pixel from the x,y coords specified and returns its colour
 * Note returned colour is a byte and represents a palette number (0-255) not a 24 bit RGB value
 *********************************************************************************************/
int ReadAPixel(int x, int y) {
	WAIT_FOR_GRAPHICS; // is graphics ready for new command
	GraphicsX1Reg = x; // write coords to x1, y1
	GraphicsY1Reg = y;
	GraphicsCommandReg = GetAPixel; // give graphics a "get pixel" command
	WAIT_FOR_GRAPHICS
	; // is graphics done reading pixel
	return (int) (GraphicsColourReg); // return the palette number (colour)
}

void ProgramPalette(int PaletteNumber, int RGB) {
	WAIT_FOR_GRAPHICS;
	GraphicsColourReg = PaletteNumber;
	GraphicsX1Reg = RGB >> 16; // program red value in ls.8 bit of X1 reg
	GraphicsY1Reg = RGB; // program green and blue into ls 16 bit of Y1 reg
	GraphicsCommandReg = ProgramPaletteColour; // issue command
}

void HLine(int x1, int y1, int length, int Colour) {
	WAIT_FOR_GRAPHICS;
	GraphicsX1Reg = x1; // write coords to x1, y1
	GraphicsY1Reg = y1;
	GraphicsX2Reg = x1 + length;
	GraphicsColourReg = Colour; // set pixel colour
	GraphicsCommandReg = DrawHLine; // give graphics "write pixel" command

}
void VLine(int x1, int y1, int length, int Colour) {
	WAIT_FOR_GRAPHICS;
	GraphicsX1Reg = x1; // write coords to x1, y1
	GraphicsY1Reg = y1;
	GraphicsY2Reg = y1 + length;
	GraphicsColourReg = Colour; // set pixel colour
	GraphicsCommandReg = DrawVLine; // give graphics "write pixel" command
}

void Line(int x1, int y1, int x2, int y2, int Colour) {
	WAIT_FOR_GRAPHICS;
	GraphicsX1Reg = x1;
	GraphicsY1Reg = y1;
	GraphicsX2Reg = x2;
	GraphicsY2Reg = y2;
	GraphicsColourReg = Colour;
	GraphicsCommandReg = DrawLine;
}

//x1, y1 are coordinates of top left corner, x2, y2 are corrdinates of bottom right corner
void Rectangle(int x1, int y1, int x2, int y2, int Colour) {
	WAIT_FOR_GRAPHICS;
	GraphicsX1Reg = x1;
	GraphicsY1Reg = y1;
	GraphicsX2Reg = x2;
	GraphicsY2Reg = y2;
	GraphicsColourReg = Colour;
	GraphicsCommandReg = DrawARectangle;
}

void Circle(int x1, int y1, int radius, int Colour) {
	WAIT_FOR_GRAPHICS;
	GraphicsX1Reg = x1;
	GraphicsY1Reg = y1;
	GraphicsY2Reg = radius;
	GraphicsColourReg = Colour;
	GraphicsCommandReg = DrawACircle;
}

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

void DLine(int x1, int y1, int x2, int y2, int Colour) {

	int x = x1;
	int y = y1;
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int s1, s2;

	int subX = x2 - x1;
	int subY = y2 - y1;

	if (subX < 0)
		s1 = -1;
	else if (subX == 0)
		s1 = 0;
	else
		s1 = 1;

	if (subY < 0)
		s2 = -1;
	else if (subX == 0)
		s2 = 0;
	else
		s2 = 1;

	int i, temp, interchange = 0, error;

	if (dx == 0 && dy == 0)
		return;
	else {
		if (dy > dx) {
			temp = dx;
			dx = dy;
			dy = temp;
			interchange = 1;
		}
		error = (dy << 1) - dx; // error = (2 * dy) - dx
		for (i = 1; i <= dx; i++) {
			WriteAPixel(x, y, Colour);
			while (error >= 0) {
				if (interchange == 1)
					x += s1;
				else
					y += s2;
				error -= (dx << 1); // error = error – (dx * 2)
			}
			if (interchange == 1)
				y += s2;
			else
				x += s1;
			error += (dy << 1); // error = error + (dy * 2)
		}
	}
}

void DRectangle(int x1, int y1, int x2, int y2, int Colour) {
	HLine(x1, y1, x2 - x1, Colour);
	HLine(x1, y2, x2 - x1, Colour);
	VLine(x1, y1, y2 - y1, Colour);
	VLine(x2, y1, y2 - y1, Colour);
}

void DRectangleFill(int x1, int y1, int x2, int y2, int Colour) {
	for (y1; y1 <= y2; y1++) {
		HLine(x1, y1, x2 - x1, Colour);
	}
}

void ClearScreen(int Colour) {
	int j;
	for (j = 0; j <= YRES; j++) {
		HLine(0, j, XRES, Colour);
	}
}

void DCircle(int x1, int y1, int radius, int Colour) {
	int x = radius;
	int y = 0;
	int err = 0;

	while (x >= y) {
		WriteAPixel(x1 + x, y1 + y, Colour);
		WriteAPixel(x1 + y, y1 + x, Colour);
		WriteAPixel(x1 - y, y1 + x, Colour);
		WriteAPixel(x1 - x, y1 + y, Colour);
		WriteAPixel(x1 - x, y1 - y, Colour);
		WriteAPixel(x1 - y, y1 - x, Colour);
		WriteAPixel(x1 + y, y1 - x, Colour);
		WriteAPixel(x1 + x, y1 - y, Colour);

		if (err <= 0) {
			y += 1;
			err += 2 * y + 1;
		}
		if (err > 0) {
			x -= 1;
			err -= 2 * x + 1;
		}
	}

}

void DFillCircle(int xo, int yo, int radius, int Colour) {
	int y, x;
	for (y = -radius; y <= radius; y++)
		for (x = -radius; x <= radius; x++)
			if (x * x + y * y <= radius * radius)
				WriteAPixel(xo + x, yo + y, Colour);
}

int checkLoginId(char* userId) {

	if (userId[0] == '0' && userId[1] == '0' && userId[2] == '0') {
		if (userId[3] == '1') {
			return 1;
		} else if (userId[3] == '2') {
			return 2;
		} else if (userId[3] == '3') {
			return 3;
		} else if (userId[3] == '4') {
			return 4;
		}
		else{
			return -1;
		}
	} else {
		return -1;
	}
}

void clearId(void) {
	int clear;
	for (clear = 0; clear < 14; clear++) {
		HLine(XRES / 2 - 25, 40 - 3 + clear, 75, WHITE);
	}
}

void drawLoginSuccessScreen(void) {
	ClearScreen(WHITE);
	char msg[] = "LOGIN SUCCESS";
	PrintStringFont2(msg, 13, XRES / 2 - 50, YRES / 2 - 3, BLACK, WHITE, 0);
}

void drawLogoutSuccessScreen(void) {
	ClearScreen(WHITE);
	char msg[] = "LOGOUT SUCCESS";
	PrintStringFont2(msg, 14, XRES / 2 - 57, YRES / 2 - 3, BLACK, WHITE, 0);
}

void drawMainScreen(int userId) {
	ClearScreen(YELLOW);
	drawCurrentUser(userId);
	DRectangleFill(XRES - 115, YRES - 60, XRES - 30, YRES - 10, RED);
	DFillCircle(XRES/2 + 150, YRES/2, 50, LIME);
	char logoutMsg[] = "Logout";
	PrintStringFont2(logoutMsg, 6, XRES-80 - 25, YRES-35-3, BLACK, RED, 0);
	char gpsSendMsg[] = "Track";
	PrintStringFont2(gpsSendMsg, 5, XRES/2-26 + 150, YRES/2-5, BLACK, LIME, 0);
	char data[] = "Current GPS Data";
	PrintStringFont2(data, 16, 40, YRES/2 - 20, BLACK, YELLOW, 0);
}

void drawLoginScreen(void) {


	ClearScreen(WHITE);
	DRectangleFill(XRES / 2 - 120, 155, XRES / 2 + 120, YRES - 10, 0x00FEFEFE);
	DRectangle(XRES / 2 - 120, 155, XRES / 2 + 120, YRES - 10, YELLOW);
	HLine(XRES / 2 - 120, 155 + 80, 240, YELLOW);
	HLine(XRES / 2 - 120, 155 + 160, 240, YELLOW);
	HLine(XRES / 2 - 120, 155 + 240, 240, YELLOW);
	VLine(XRES / 2 - 40, 155, 240, YELLOW);
	VLine(XRES / 2 + 40, 155, 240, YELLOW);
	VLine(XRES / 2 - 40, 155 + 240, 80, YELLOW);

	int thickness;
	for (thickness = 0; thickness <= 3; thickness++) {
		HLine(XRES / 2 - 28, 55 + thickness, 58, BLACK); //Might have to change y position
	}

	OutGraphicsCharFont2(320 - 3, 195 - 3, BLACK, 0x00FEFEFE, '1', 0);
	OutGraphicsCharFont2(400 - 3, 195 - 3, BLACK, 0x00FEFEFE, '2', 0);
	OutGraphicsCharFont2(480 - 3, 195 - 3, BLACK, 0x00FEFEFE, '3', 0);
	OutGraphicsCharFont2(320 - 3, 275 - 3, BLACK, 0x00FEFEFE, '4', 0);
	OutGraphicsCharFont2(400 - 3, 275 - 3, BLACK, 0x00FEFEFE, '5', 0);
	OutGraphicsCharFont2(480 - 3, 275 - 3, BLACK, 0x00FEFEFE, '6', 0);
	OutGraphicsCharFont2(320 - 3, 355 - 3, BLACK, 0x00FEFEFE, '7', 0);
	OutGraphicsCharFont2(400 - 3, 355 - 3, BLACK, 0x00FEFEFE, '8', 0);
	OutGraphicsCharFont2(480 - 3, 355 - 3, BLACK, 0x00FEFEFE, '9', 0);
	OutGraphicsCharFont2(320 - 3, 435 - 3, BLACK, 0x00FEFEFE, '0', 0);

	char enter[] = "ENTER";
	PrintStringFont2(enter, 5, 440 - 30, 435 - 7, BLACK, 0x00FEFEFE, 0);

	drawLogo(XRES/13, YRES/2);
	char title[] = "TrailSec";
	PrintStringFont2(title, 8, 3*XRES/4, YRES/2 - 3, BLACK, 0x00FEFEFE, 0);


}

void displayPopup(char* msg, int size, int backgroundColour) {
	int hIndex;
	for (hIndex = 0; hIndex < 150; hIndex++) {
		HLine(XRES / 2 - 200, YRES / 2 - 150 + hIndex, 400, backgroundColour);
	}
	PrintStringFont2(msg, size, XRES / 2 - size * 5, YRES / 2 - 3 - 100, BLACK,
			backgroundColour, 0);
	DRectangleFill(XRES / 2 - 30, YRES / 2 - 60, XRES / 2 + 30, YRES / 2 - 15,
			RED);
	char okMsg[] = "ok";
	PrintStringFont2(okMsg, 2, XRES / 2 - 12, YRES / 2 - 38 - 3, BLACK, RED, 0);

	Point pT;
	Point pR;

	while (1) {
		pT = TouchPressed();
		pR = TouchRelease();
		if (pR.x >= XRES / 2 - 30 && pR.y >= YRES / 2 - 60
				&& pR.x <= XRES / 2 + 30 && pR.y <= YRES / 2 - 15) {
			printf("ok pressed");
			break;
		}
	}
}

int loginVerification(void) {

	char userId[4];
	bool enterPressed = false;
	bool loginfinished = false;
	bool passwordVerify = false;
	int idLength = 0;
	Point pT;
	Point pR;
	int checkId;
	while (!loginfinished) {
		pT = TouchPressed();
		pR = TouchRelease();
		if (pR.x >= 280 && pR.x < 360 && pR.y >= 155 && pR.y < 235) {
			userId[idLength] = '1';
			idLength++;
			printf("Pressed 1\n");
		} else if (pR.x >= 360 && pR.x < 440 && pR.y >= 155 && pR.y < 235) {
			userId[idLength] = '2';
			idLength++;
			printf("Pressed 2\n");
		} else if (pR.x >= 440 && pR.x < 520 && pR.y >= 155 && pR.y < 235) {
			userId[idLength] = '3';
			idLength++;
			printf("Pressed 3\n");
		} else if (pR.x >= 280 && pR.x < 360 && pR.y >= 235 && pR.y < 315) {
			userId[idLength] = '4';
			idLength++;
			printf("Pressed 4\n");
		} else if (pR.x >= 360 && pR.x < 440 && pR.y >= 235 && pR.y < 315) {
			userId[idLength] = '5';
			idLength++;
			printf("Pressed 5\n");
		} else if (pR.x >= 440 && pR.x < 520 && pR.y >= 235 && pR.y < 315) {
			userId[idLength] = '6';
			idLength++;
			printf("Pressed 6\n");
		} else if (pR.x >= 280 && pR.x < 360 && pR.y >= 315 && pR.y < 395) {
			userId[idLength] = '7';
			idLength++;
			printf("Pressed 7\n");
		} else if (pR.x >= 360 && pR.x < 440 && pR.y >= 315 && pR.y < 395) {
			userId[idLength] = '8';
			idLength++;
			printf("Pressed 8\n");
		} else if (pR.x >= 440 && pR.x < 520 && pR.y >= 315 && pR.y < 395) {
			userId[idLength] = '9';
			idLength++;
			printf("Pressed 9\n");
		} else if (pR.x >= 280 && pR.x < 360 && pR.y >= 395 && pR.y < 475) {
			userId[idLength] = '0';
			idLength++;
			printf("Pressed 0\n");
		} else if (pR.x >= 360 && pR.x < 520 && pR.y >= 395 && pR.y < 475) {
			enterPressed = true;
			printf("Pressed Enter\n");
		} else {
			enterPressed = false;
			printf("Invalid press\n");
		}

		if (enterPressed == true) {
			if(passwordVerify == true){
				if (idLength == 4) {
					if (passwordVerification(checkId, userId)) {
						printf("Login Successs!\n");
						loginfinished = true;
						drawLoginSuccessScreen();
						usleep(2000000);
						break;
					}
					else {
						idLength = 0;
						clearId();
						enterPressed = false;
						char err[] = "Invalid Password!";
						displayPopup(err, 17, YELLOW);
						printf("Invalid Password\n");
						drawLoginScreen();
						drawUserPasswordPrompt(checkId);
						//Added draw password message
					}
				}
			}
			else{
				if (idLength == 4) {
					checkId = checkLoginId(userId);
					printf("Check Id is: %d\n", checkId);
					if (checkId > 0 && checkId <= 4) {
						//TODO: Password verify (DONE?)
						passwordVerify = true;
						enterPressed = false;
						idLength = 0;
						clearId();
						drawUserPasswordPrompt(checkId);
						continue;
						//printf("Login Successs!\n");
						//loginfinished = true;
						//drawLoginSuccessScreen();
						//usleep(2000000);
						//break;
					} else {
						idLength = 0;
						clearId();
						enterPressed = false;
						char err[] = "Invalid UserId";
						displayPopup(err, 14, YELLOW);
						printf("Invalid userId\n");
						drawLoginScreen();
					}
				}
				else {
					idLength = 0;
					clearId();
					enterPressed = false;
					char err[] = "Invalid Input";
					displayPopup(err, 13, YELLOW);
					printf("Invalid Input\n");
					drawLoginScreen();
				}
			}
		}
		else {
			if(passwordVerify){
				if (idLength == 1) {
					OutGraphicsCharFont2(XRES / 2 - 25, 40 - 3, BLACK, WHITE, '*', 0);
				}
				else if (idLength == 2) {
					OutGraphicsCharFont2(XRES / 2 - 10, 40 - 3, BLACK, WHITE, '*', 0);
				}
				else if (idLength == 3) {
					OutGraphicsCharFont2(XRES / 2 + 5, 40 - 3, BLACK, WHITE, '*', 0);
				}
				else if (idLength == 4) {
					OutGraphicsCharFont2(XRES / 2 + 20, 40 - 3, BLACK, WHITE, '*', 0);
				}
			}
			else{
				printf("the length is: %d", idLength);
				if (idLength == 1) {
					OutGraphicsCharFont2(XRES / 2 - 25, 40 - 3, BLACK, WHITE, userId[0], 0);
				}
				else if (idLength == 2) {
					OutGraphicsCharFont2(XRES / 2 - 10, 40 - 3, BLACK, WHITE, userId[1], 0);
				}
				else if (idLength == 3) {
					OutGraphicsCharFont2(XRES / 2 + 5, 40 - 3, BLACK, WHITE, userId[2], 0);
				}
				else if (idLength == 4) {
					OutGraphicsCharFont2(XRES / 2 + 20, 40 - 3, BLACK, WHITE, userId[3], 0);
				}
			}
		}
	}
	return checkId;
}

void drawCurrentUser(int userIndex){
	if (userIndex == 1){
		char name[] = "User: Tony Wang";
		char id[] = "Id: 0001";
		PrintStringFont2(name, 15, 40, 10, BLACK, YELLOW, 0);
		PrintStringFont2(id, 8, 40, 30, BLACK, WHITE, 0);
	}
	else if(userIndex == 2){
		char name[] = "User: Alexander Julianto";
		char id[] = "Id: 0002";
		PrintStringFont2(name, 24, 40, 10, BLACK, YELLOW, 0);
		PrintStringFont2(id, 8, 40, 30, BLACK, WHITE, 0);
	}
	else if(userIndex == 3){
		char name[] = "User: Justin Toh";
		char id[] = "Id: 0003";
		PrintStringFont2(name, 16, 40, 10, BLACK, YELLOW, 0);
		PrintStringFont2(id, 8, 40, 30, BLACK, WHITE, 0);
	}
	else if(userIndex == 4){
		char name[] = "User: James Zhou";
		char id[] = "Id: 0004";
		PrintStringFont2(name, 16, 40, 10, BLACK, YELLOW, 0);
		PrintStringFont2(id, 8, 40, 30, BLACK, WHITE, 0);
	}
}

void mainScreenFunctionality(){
	Point pT;
	Point pR;

	while(1){
		pT = TouchPressed();
		pR = TouchRelease();
		if (pR.x >= XRES/2 - 50 + 150 && pR.x < XRES/2 + 50 + 150 && pR.y >= YRES/2 - 50 && pR.y < YRES/2 + 50){
			printf("Sending GPS coordinates\n");
			DRectangleFill(40, YRES/2 , 250, YRES/2 + 50, YELLOW);
			drawSendingGPS();
			read_gps_data();
			DRectangleFill(XRES/2 - 140, YRES/2 - 20, XRES/2 + 80, YRES/2 + 20, YELLOW);
		}
		else if (pR.x >= XRES -115 && pR.x < XRES - 30 && pR.y >= YRES - 60 && pR.y < YRES - 10){
			printf("Logged out!\n");
			drawLogoutSuccessScreen();
			usleep(2000000);
			break;
		}
	}
}

int passwordVerification(int userIndex, char* password){

	if (userIndex == 1){
		if (password[0] == '1' && password[1] == '2' && password[2] == '3' && password[3] == '4') {
			return true;
		} else{
			return false;
		}
	}
	else if (userIndex == 2){
		if (password[0] == '5' && password[1] == '6' && password[2] == '7' && password[3] == '8') {
			return true;
		} else{
			return false;
		}
	}
	else if (userIndex == 3){
		if (password[0] == '0' && password[1] == '9' && password[2] == '8' && password[3] == '7') {
			return true;
		} else{
			return false;
		}
	}
	else if (userIndex == 4){
		if (password[0] == '6' && password[1] == '5' && password[2] == '4' && password[3] == '3') {
			return true;
		} else{
			return false;
		}
	}
	else{
		return false;
	}
}

void drawUserPasswordPrompt(int userIndex){
	if (userIndex == 1){
		char name[] = "User: Tony Wang";
		PrintStringFont2(name, 15, 40, 10, BLACK, WHITE, 0);
	}
	else if(userIndex == 2){
		char name[] = "User: Alexander Julianto";
		PrintStringFont2(name, 24, 40, 10, BLACK, WHITE, 0);
	}
	else if(userIndex == 3){
		char name[] = "User: Justin Toh";
		PrintStringFont2(name, 16, 40, 10, BLACK, WHITE, 0);
	}
	else if(userIndex == 4){
		char name[] = "User: James Zhou";
		PrintStringFont2(name, 16, 40, 10, BLACK, WHITE, 0);
	}
	else{
		return;
	}
	char prompt[] = "Please Enter Your Password";
	PrintStringFont2(prompt, 26, 40, 30, BLACK, WHITE, 0);
}

void drawGPSData(char* longitude, char* latitude){
		char data[] = "Current GPS Data";
		PrintStringFont2(data, 16, 40, YRES/2 - 20, BLACK, YELLOW, 0);
		PrintStringFont2(longitude, 10, 40, YRES/2, BLACK, YELLOW, 0);
		PrintStringFont2(latitude, 10, 40, YRES/2 + 20, BLACK, YELLOW, 0);
}

void drawIntroScreen(void){
	Point pT;
	Point pR;

	ClearScreen(LIME);
	drawLogo(XRES/6, YRES/2 - 40);

	char nameProject[] = "Group 14: TrailSec";

	char nameAlex[] = "Alexander Julianto";
	char nameJames[] = "James Zhou";
	char nameJustin[] = "Justin Toh";
	char nameTony[] = "Tony Wang";

	PrintStringFont2(nameProject, 18, XRES/2 - 7 * 15, YRES/2, BLACK, LIME, 0);


	PrintStringFont2(nameAlex, 18, XRES/2 - 7 * 15, YRES/2 + 40, BLACK, LIME, 0);
	PrintStringFont2(nameJames, 10, XRES/2 - 4 * 15, YRES/2 + 60, BLACK, LIME, 0);
	PrintStringFont2(nameJustin, 10, XRES/2 - 4 * 15, YRES/2 + 80, BLACK, LIME, 0);
	PrintStringFont2(nameTony, 9, XRES/2 - 4 * 15, YRES/2 + 100, BLACK, LIME, 0);


	pT = TouchPressed();
	pR = TouchRelease();
	return;
}

void drawPixelBlock(int x, int y, int Colour){

	int X = x*3;
	int Y = y*3;

	WriteAPixel(X, Y, BLACK);
	WriteAPixel(X, Y-1, BLACK);
	WriteAPixel(X, Y+1, BLACK);
	WriteAPixel(X-1, Y-1, BLACK);
	WriteAPixel(X-1, Y, BLACK);
	WriteAPixel(X-1, Y+1, BLACK);
	WriteAPixel(X+1, Y-1, BLACK);
	WriteAPixel(X+1, Y, BLACK);
	WriteAPixel(X+1, Y+1, BLACK);
}

//assume corrdinates are XRES/2 and YRES/2
void drawLogo(int x, int y){
	drawPixelBlock(x, y, BLACK);
	drawPixelBlock(x-1, y+1, BLACK);
	drawPixelBlock(x-2, y+1, BLACK);
	drawPixelBlock(x-3, y+2, BLACK);
	drawPixelBlock(x-4, y+2, BLACK);
	drawPixelBlock(x-5, y+3, BLACK);
	drawPixelBlock(x-6, y+3, BLACK);
	drawPixelBlock(x-7, y+4, BLACK);
	drawPixelBlock(x-8, y+4, BLACK);
	drawPixelBlock(x-9, y+4, BLACK);

	drawPixelBlock(x+1, y+1, BLACK);
	drawPixelBlock(x+2, y+1, BLACK);
	drawPixelBlock(x+3, y+2, BLACK);
	drawPixelBlock(x+4, y+2, BLACK);
	drawPixelBlock(x+5, y+3, BLACK);
	drawPixelBlock(x+6, y+3, BLACK);
	drawPixelBlock(x+7, y+4, BLACK);
	drawPixelBlock(x+8, y+4, BLACK);
	drawPixelBlock(x+9, y+4, BLACK);

	drawPixelBlock(x-9, y+5, BLACK);
	drawPixelBlock(x-9, y+6, BLACK);
	drawPixelBlock(x-9, y+7, BLACK);
	drawPixelBlock(x-9, y+8, BLACK);
	drawPixelBlock(x+9, y+5, BLACK);
	drawPixelBlock(x+9, y+6, BLACK);
	drawPixelBlock(x+9, y+7, BLACK);
	drawPixelBlock(x+9, y+8, BLACK);

	drawPixelBlock(x-8, y+9, BLACK);
	drawPixelBlock(x-8, y+10, BLACK);
	drawPixelBlock(x-8, y+11, BLACK);
	drawPixelBlock(x-8, y+12, BLACK);
	drawPixelBlock(x+8, y+9, BLACK);
	drawPixelBlock(x+8, y+10, BLACK);
	drawPixelBlock(x+8, y+11, BLACK);
	drawPixelBlock(x+8, y+12, BLACK);

	drawPixelBlock(x-7, y+13, BLACK);
	drawPixelBlock(x-7, y+14, BLACK);
	drawPixelBlock(x-7, y+15, BLACK);
	drawPixelBlock(x+7, y+13, BLACK);
	drawPixelBlock(x+7, y+14, BLACK);
	drawPixelBlock(x+7, y+15, BLACK);

	drawPixelBlock(x-6, y+16, BLACK);
	drawPixelBlock(x-6, y+17, BLACK);
	drawPixelBlock(x+6, y+16, BLACK);
	drawPixelBlock(x+6, y+17, BLACK);

	drawPixelBlock(x-5, y+18, BLACK);
	drawPixelBlock(x+5, y+18, BLACK);

	drawPixelBlock(x-4, y+19, BLACK);
	drawPixelBlock(x+4, y+19, BLACK);

	drawPixelBlock(x-3, y+20, BLACK);
	drawPixelBlock(x+3, y+20, BLACK);

	drawPixelBlock(x-2, y+21, BLACK);
	drawPixelBlock(x-1, y+21, BLACK);
	drawPixelBlock(x+2, y+21, BLACK);
	drawPixelBlock(x+1, y+21, BLACK);

	drawPixelBlock(x, y+22, BLACK);
}

void drawSendingGPS(void){
	 DRectangleFill(XRES/2 - 140, YRES/2 - 20, XRES/2 + 80, YRES/2 + 20, LIME);
	 char loading[] = "Sending GPS Data...";
	 PrintStringFont2(loading, 19, XRES/2-30 - 7 * 15, YRES/2, BLACK, LIME, 0);
}

void drawLoadingBar(int p){
	 DRectangleFill(XRES/2 - 135, YRES/2 - 55, XRES/2 + 105, XRES/2 + 55, BLUE);
	 DRectangleFill(XRES/2 - 130, YRES/2 - 50, XRES/2 + 100, XRES/2 + 50, YELLOW);
}
