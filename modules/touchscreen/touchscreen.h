#include <stdbool.h>

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    int x;
    int y;
    int height;
    int width;
} Box;

#define TOUCHSCREEN_CONTROL (*(volatile unsigned char *)(0x84000230))
#define TOUCHSCREEN_STATUS (*(volatile unsigned char *)(0x84000230))
#define TOUCHSCREEN_TXDATA (*(volatile unsigned char *)(0x84000232))
#define TOUCHSCREEN_RXDATA (*(volatile unsigned char *)(0x84000232))
#define TOUCHSCREEN_BAUD (*(volatile unsigned char *)(0x84000234))
#define TOUCHSCREEN_STATUS_TX_MASK 0x02
#define TOUCHSCREEN_STATUS_RX_MASK 0x01

void TOUCH_init(void);
void TOUCH_waitForTouchEvent(void);
int  TOUCH_putChar(char c);
char TOUCH_getChar(void);
Point TOUCH_getTouchCoordinates(int PorR);
Point TOUCH_onTouch(void);
Point TOUCH_onRelease(void);

/* helper methods */
bool TOUCH_isPointInsideBox(Point touchInput, Box touchArea);
Box TOUCH_createBox(int x, int y, int height, int width);
