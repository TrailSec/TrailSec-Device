/* Main function that handles which view to load at a given state */
int loadView(int view_state);

/* Loads the UI, bluetooth + touchscreen event listeners for each view */
int loadView_splashscreen(void);
int loadView_bluetoothpairing(void);
int loadView_main(void);