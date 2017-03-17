#define GraphicsCommandReg (*(volatile unsigned short int *)(0x84000000))
#define GraphicsStatusReg (*(volatile unsigned short int *)(0x84000000))
#define GraphicsX1Reg (*(volatile unsigned short int *)(0x84000002))
#define GraphicsY1Reg (*(volatile unsigned short int *)(0x84000004))
#define GraphicsX2Reg (*(volatile unsigned short int *)(0x84000006))
#define GraphicsY2Reg (*(volatile unsigned short int *)(0x84000008))
#define GraphicsColourReg (*(volatile unsigned short int *)(0x8400000E))
#define GraphicsBackGroundColourReg (*(volatile unsigned short int *)(0x84000010))

#define Touch_Control (*(volatile unsigned char *)(0x84000230))
#define Touch_Status (*(volatile unsigned char *)(0x84000230))
#define TouchScreen_TX (*(volatile unsigned char *)(0x84000232))
#define TouchScreen_RX (*(volatile unsigned char *)(0x84000232))
#define Touch_Baud (*(volatile unsigned char *)(0x84000234))

#define WAIT_FOR_GRAPHICS while((GraphicsStatusReg & 0x0001) != 0x0001);

// #defined constants representing values we write to the graphics 'command' register to get
// it to draw something. You will add more values as you add hardware to the graphics chip
// Note DrawHLine, DrawVLine and DrawLine at the moment do nothing - you will modify these
#define DrawHLine 1
#define DrawVLine 2
#define DrawLine 3
#define PutAPixel 0xA
#define GetAPixel 0xB
#define ProgramPaletteColour 0x10
#define DrawARectangle 4
#define DrawACircle 5

#define BLACK 0
#define WHITE 1
#define RED 2
#define LIME 3
#define BLUE 4
#define YELLOW 5
#define CYAN 6
#define MAGENTA 7

#define XRES 800
#define YRES 480

typedef struct {
	int x;
	int y;
} Point;

void WriteAPixel(int x, int y, int Colour);
int ReadAPixel(int x, int y);
void ProgramPalette(int PaletteNumber, int RGB);
void HLine(int x1, int y1, int length, int Colour);
void VLine(int x1, int y1, int length, int Colour);
void Line(int x1, int y1, int x2, int y2, int Colour);
void Rectangle(int x1, int y1, int x2, int y2, int Colour);
void Circle(int x1, int y1, int radius, int Colour);
void Init_Touch(void);
void WaitingForTouch(void);
Point getTouchCoordinates(int PorR);
Point TouchPressed(void);
Point TouchRelease(void);
int inputTouchScreenChar(int character);
int outputTouchScreenChar(void);
void DLine(int x1, int y1, int x2, int y2, int Colour);
void DRectangle(int x1, int y1, int x2, int y2, int Colour);
void DRectangleFill(int x1, int y1, int x2, int y2, int Colour);
void ClearScreen(int Colour);
void DCircle(int x1, int y1, int radius, int Colour);
void DFillCircle(int xo, int yo, int radius, int Colour);
int checkLoginId(char* userId);
void clearId(void);
void drawLoginSuccessScreen(void);
void drawLogoutSuccessScreen(void);
void drawMainScreen(int userId);
void drawLoginScreen(void);
void displayPopup(char* msg, int size, int backgroundColour);
int loginVerification(void);
void drawCurrentUser(int userIndex);
void mainScreenFunctionality(void);
int passwordVerification(int userIndex, char* password);
void drawUserPasswordPrompt(int userIndex);
void drawGPSData(char* longitude, char* latitude);
void drawIntroScreen(void);
void drawPixelBlock(int x, int y, int Colour);
void drawLogo(int x, int y);
void drawSendingGPS(void);
void drawLoadingBar(int p);



