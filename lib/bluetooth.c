#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "bluetooth.h"

// Confire serial port (Baud = 115Kbps, 8 bits of data, no parity, 1 stop bit)
void init_bluetooth(void)
{
    BLUETOOTH_CONTROL = 0x15;
    BLUETOOTH_BAUD = 0x01;
}

// Write 1-byte of data into serial port [BLUETOOTH]
void putchar_bluetooth(char c)
{
    while ((BLUETOOTH_STATUS & 0x02) != 0x02);
    BLUETOOTH_TXDATA = c & 0xFF;
}

// Write a string (series of 1-byte data) into serial port [BLUETOOTH]
void putString_bluetooth(char *s)
{
    int i;
    for(i=0; s[i]!='\0'; i++){
        putchar_bluetooth((char) s[i]);
    }
}

// Function blocks till serial port read status is ready
void wait_for_read_ready_bluetooth()
{
    while((BLUETOOTH_STATUS & 0x01) != 0x01);
}

// Read 1-byte of data from serial port [BLUETOOTH]
char getchar_bluetooth(void)
{
    wait_for_read_ready_bluetooth();
    return BLUETOOTH_RXDATA;
}

// Reads a string from serial port [BLUETOOTH]
int getCommand_bluetooth(char *str_buffer, int buflen)
{
	int i=0;
    for (i = 0; i < buflen; i++) {
        char charRx = getchar_bluetooth();
        str_buffer[i] = charRx;

        if (charRx == '\0') {
            return i;
        }
    }

    // Input string exceeds buffer length
    return -1;
}

// Helper function: Enter bluetooth dongle's command mode
void enter_command_mode(){
    printf("ENTERING COMMAND MODE...\n");
    putString_bluetooth("$$$");
    usleep(BLUETOOTH_COMMAND_DELAY);
}

// Helper function: Exit bluetooth dongle's command mode
void exit_command_mode(){
    printf("EXITING COMMAND MODE...\n");
    putString_bluetooth("---\r\n");
    usleep(BLUETOOTH_COMMAND_DELAY);
}

// Set bluetooth dongle's device name
void set_device_name(char *s){
    printf("SETTING DEVICE NAME...\n");
    enter_command_mode();
    putString_bluetooth("SN,");
    putString_bluetooth(s);
    putString_bluetooth("\r\n");
    usleep(BLUETOOTH_COMMAND_DELAY);
    exit_command_mode();
}

// Set bluetooth dongle's device pin
void set_device_pin(char *s){
    printf("SETTING DEVICE PIN...\n");
    enter_command_mode();
    putString_bluetooth("SP,");
    putString_bluetooth(s);
    putString_bluetooth("\r\n");
    usleep(BLUETOOTH_COMMAND_DELAY);
    exit_command_mode();
}

// Reset bluetooth dongle's back to factory setting
void reset_to_factory_defaults(){
    printf("PERFORMING FACTORY RESET...\n");
    enter_command_mode();
    putString_bluetooth("SF,1\r\n");
    usleep(BLUETOOTH_COMMAND_DELAY);
    exit_command_mode();
}

// **NOTE** This test only works when de1 board's bluetooth TX pin is directly to RX pin
void test_bluetooth_serial_ports(){
    printf("EXECUTING test_bluetooth_serial_ports()...\n");

    init_bluetooth();
    printf("> BLUETOOTH INITIALIZED\n");

    int i;
    for(i=0; i<255; i++){
        putchar_bluetooth((char) i);
        printf("> RECEIVE: %c\n", getchar_bluetooth());
    }

    printf("test_bluetooth_serial_ports() COMPLETED!\n");
}

// Configures the bluetooth dongle's DEVICE-NAME + PIN
void configure_bluetooth_dongle(){
    printf("> INITIALIZING BLUETOOTH...\n");

    init_bluetooth();
    printf("> BLUETOOTH INITIALIZED\n");

    set_device_name("CPEN391-GRP14-YUGER-D");
    printf("> BLUETOOTH DEVICE-NAME CHANGED\n");

    set_device_pin("9999");
    printf("> BLUETOOTH DEVICE-PIN CHANGED\n");

    printf("> BLUETOOTH CONFIGURATION COMPLETED!\n");
}
