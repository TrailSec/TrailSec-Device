typedef struct {
    int x;
    int y;
} Point;

#define TOUCHSCREEN_CONTROL (*(volatile unsigned char *)(0x84000230))
#define TOUCHSCREEN_STATUS (*(volatile unsigned char *)(0x84000230))
#define TOUCHSCREEN_TXDATA (*(volatile unsigned char *)(0x84000232))
#define TOUCHSCREEN_RXDATA (*(volatile unsigned char *)(0x84000232))
#define TOUCHSCREEN_BAUD (*(volatile unsigned char *)(0x84000234))
#define TOUCHSCREEN_STATUS_TX_MASK 0x02
#define TOUCHSCREEN_STATUS_RX_MASK 0x01

void Init_Touch(void);
void WaitingForTouch(void);
Point getTouchCoordinates(int PorR);
Point TouchPressed(void);
Point TouchRelease(void);
int inputTouchScreenChar(int character);
int outputTouchScreenChar(void);
