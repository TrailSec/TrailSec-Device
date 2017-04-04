/* UI + Image dimensions */
#define WATCHFRAME_WIDTH 300
#define WATCHFRAME_HEIGHT 500
#define VIEW_WIDTH 160
#define VIEW_HEIGHT 200
#define WATCHFRAME_TO_VIEW_OFFSET_X 70
#define WATCHFRAME_TO_VIEW_OFFSET_Y 150

#define WATCHFRAME_POSITION_X 250
#define WATCHFRAME_POSITION_Y 0
#define VIEW_POSITION_X (WATCHFRAME_POSITION_X + WATCHFRAME_TO_VIEW_OFFSET_X)
#define VIEW_POSITION_Y (WATCHFRAME_POSITION_Y + WATCHFRAME_TO_VIEW_OFFSET_Y)

/* Watch frame */
void drawWatchframe();

/* UI views */
void drawView_splashscreen();
void drawView_bluetoothPairing();
void drawView_main();
