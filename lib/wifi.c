#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "wifi.h"

void init_wifi(void)
{
    WIFI_CONTROL = 0x15;
    WIFI_BAUD = 0x01;
    putString_wifi("\n");
    usleep(1000);
    putString_wifi("\n");
    putString_wifi("dofile(\"twilio.lua\")"); //even though the file is called twilio.lua,
    											// this script connects to the firebase
    putString_wifi("\n");
}

// Blocks the serial port until it is ready
void wait_for_read_ready()
{
    while((WIFI_STATUS & 0x01) != 0x01);
}

// Write 1 byte of data into the WIFI serial port
void putchar_wifi(char c)
{
    while ((WIFI_STATUS & 0x02) != 0x02);
    WIFI_TXDATA = c & 0xFF;
}

// Write a string into the wifi TX port
void putString_wifi(char *s)
{
    int i;
    for(i=0; s[i]!='\0'; i++){
        putchar_wifi((char) s[i]);
    }
}

char getchar_wifi(void)
{
    wait_for_read_ready();
    return WIFI_RXDATA;
}
