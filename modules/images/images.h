#define WATCHFRAME_RESERVED_PALETTE_COUNT 32

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

/* VIEW ID */
#define VIEW_SPLASHSCREEN_ID 0
#define VIEW_BLUETOOTHPAIRING_ID 1
#define VIEW_MAIN_ID 2
#define VIEW_CHECKIN_ID 3

/* Handles view routing */
int loadView(int view_state);

/* Watch frame */
void drawWatchframe();

/* UI views */
void drawView_splashscreen();
void drawView_bluetoothPairing();
void drawView_main();
void drawView_checkIn();
