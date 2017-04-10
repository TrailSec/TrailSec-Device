#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "bluetooth.h"

// Configure serial port (Baud = 115Kbps, 8 bits of data, no parity, 1 stop bit)
void BLUETOOTH_init(void)
{
    BLUETOOTH_CONTROL = 0x15;
    BLUETOOTH_BAUD = 0x01;
}

// Write 1-byte of data into serial port [BLUETOOTH]
void BLUETOOTH_putChar(char c)
{
    while ((BLUETOOTH_STATUS & BLUETOOTH_STATUS_TX_MASK) != BLUETOOTH_STATUS_TX_MASK);
    BLUETOOTH_TXDATA = c & 0xFF;
}

// Write a string (series of 1-byte data) into serial port [BLUETOOTH]
void BLUETOOTH_putString(char *s)
{
    int i;
    for(i=0; s[i]!='\0'; i++){
        BLUETOOTH_putChar((char) s[i]);
    }
}

// Function blocks till serial port read status is ready
void BLUETOOTH_waitForReadReady()
{
    while((BLUETOOTH_STATUS & BLUETOOTH_STATUS_RX_MASK) != BLUETOOTH_STATUS_RX_MASK);
}

// Read 1-byte of data from serial port [BLUETOOTH]
char BLUETOOTH_getChar(void)
{
    BLUETOOTH_waitForReadReady();
    return BLUETOOTH_RXDATA;
}

// Reads a string from serial port [BLUETOOTH]
int BLUETOOTH_getString(char *str_buffer, int buflen)
{
    int i=0;
    for (i = 0; i < buflen; i++) {
        char charRx = BLUETOOTH_getChar();
        str_buffer[i] = charRx;

        if (charRx == '\n') {
            return i;
        }
    }

    // Input string exceeds buffer length
    return -1;
}

// Helper function: Enter bluetooth dongle's command mode
void BLUETOOTH_enterCommandMode(){
    printf("ENTERING COMMAND MODE...\n");
    BLUETOOTH_putString("$$$");
    usleep(BLUETOOTH_COMMAND_DELAY);
}

// Helper function: Exit bluetooth dongle's command mode
void BLUETOOTH_exitCommandMode(){
    printf("EXITING COMMAND MODE...\n");
    BLUETOOTH_putString("---\r\n");
    usleep(BLUETOOTH_COMMAND_DELAY);
}

// Set bluetooth dongle's device name
void BLUETOOTH_setDeviceName(char *s){
    printf("SETTING DEVICE NAME...\n");
    BLUETOOTH_enterCommandMode();
    BLUETOOTH_putString("SN,");
    BLUETOOTH_putString(s);
    BLUETOOTH_putString("\r\n");
    usleep(BLUETOOTH_COMMAND_DELAY);
    BLUETOOTH_exitCommandMode();
}

// Set bluetooth dongle's device pin
void BLUETOOTH_setDevicePin(char *s){
    printf("SETTING DEVICE PIN...\n");
    BLUETOOTH_enterCommandMode();
    BLUETOOTH_putString("SP,");
    BLUETOOTH_putString(s);
    BLUETOOTH_putString("\r\n");
    usleep(BLUETOOTH_COMMAND_DELAY);
    BLUETOOTH_exitCommandMode();
}

// Reset bluetooth dongle's back to factory setting
void BLUETOOTH_factoryReset(){
    printf("PERFORMING FACTORY RESET...\n");
    BLUETOOTH_enterCommandMode();
    BLUETOOTH_putString("SF,1\r\n");
    usleep(BLUETOOTH_COMMAND_DELAY);
    BLUETOOTH_exitCommandMode();
}

// **NOTE** This test only works when de1 board's bluetooth TX pin is directly to RX pin
void BLUETOOTH_testSerialPorts(){
    printf("EXECUTING BLUETOOTH_testSerialPorts()...\n");

    BLUETOOTH_init();
    printf("> BLUETOOTH INITIALIZED\n");

    int i;
    for(i=0; i<255; i++){
        BLUETOOTH_putChar((char) i);
        printf("> RECEIVE: %c\n", BLUETOOTH_getChar());
    }

    printf("BLUETOOTH_testSerialPorts() COMPLETED!\n");
}

// Configures the bluetooth dongle's DEVICE-NAME + PIN
void BLUETOOTH_configureModule(){
    printf("> INITIALIZING BLUETOOTH...\n");

    BLUETOOTH_init();
    printf("> BLUETOOTH INITIALIZED\n");

    BLUETOOTH_setDeviceName("CPEN391-TRAILSEC-DEVICE");
    printf("> BLUETOOTH DEVICE-NAME CHANGED\n");

    BLUETOOTH_setDevicePin("9999");
    printf("> BLUETOOTH DEVICE-PIN CHANGED\n");

    printf("> BLUETOOTH CONFIGURATION COMPLETED!\n");
}
