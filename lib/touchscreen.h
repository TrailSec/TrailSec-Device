#include "graphics.h"

#define Touch_Control (*(volatile unsigned char *)(0x84000230))
#define Touch_Status (*(volatile unsigned char *)(0x84000230))
#define TouchScreen_TX (*(volatile unsigned char *)(0x84000232))
#define TouchScreen_RX (*(volatile unsigned char *)(0x84000232))
#define Touch_Baud (*(volatile unsigned char *)(0x84000234))

typedef struct {
	int x;
	int y;
} Point;

void Init_Touch(void);
void WaitingForTouch(void);
Point getTouchCoordinates(int PorR);
Point TouchPressed(void);
Point TouchRelease(void);
int inputTouchScreenChar(int character);
int outputTouchScreenChar(void);
