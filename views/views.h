/* VIEW ID */
#define VIEW_SPLASHSCREEN_ID 0
#define VIEW_BLUETOOTHPAIRING_ID 1
#define VIEW_MAIN_ID 2
#define VIEW_CHECKIN_ID 3

/* Main function that handles which view to load at a given state */
int loadView(int view_state);

/* Loads the UI, bluetooth + touchscreen event listeners for each view */
int loadView_splashscreen(void);
int loadView_bluetoothPairing(void);
int loadView_main(void);
int loadView_checkIn(void);