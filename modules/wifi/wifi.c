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
    putString_wifi("dofile(\"twilio.lua\")");
    putString_wifi("\n");
}

// Blocks the serial port until it is ready
void wait_for_read_ready()
{
    while((WIFI_STATUS & WIFI_STATUS_RX_MASK) != WIFI_STATUS_RX_MASK);
}

// Write 1 byte of data into the WIFI serial port
void putchar_wifi(char c)
{
    while ((WIFI_STATUS & WIFI_STATUS_TX_MASK) != WIFI_STATUS_TX_MASK);
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

void WIFI_sendCoordinates(char *latitude, char *longitude) {

    int i, total_len = 0;

    char wifi_command_str[100] = "";
    char str0[] = "send_coor(\"";
    char str2[] = "\", \"";
    char str3[] = "\")";

    // send_coor(\"
    for (i = 0; str0[i] != '\0'; i++, total_len++) {
        wifi_command_str[total_len] = str0[i];
    }

    // send_coor(\"XX.XXXX
    for (i = 0; latitude[i] != '\0'; i++, total_len++) {
        wifi_command_str[total_len] = latitude[i];
    }

    // send_coor(\"XX.XXXX\", \"
    for (i = 0; str2[i] != '\0'; i++, total_len++) {
        wifi_command_str[total_len] = str2[i];
    }

    // send_coor(\"XX.XXXX\", \"YY.YYYY
    for (i = 0; longitude[i] != '\0'; i++, total_len++) {
        wifi_command_str[total_len] = longitude[i];
    }

    // send_coor(\"XX.XXXX\", \"YY.YYYY\")
    for (i = 0; str3[i] != '\0'; i++, total_len++) {
        wifi_command_str[total_len] = str3[i];
    }

    // Append NULL-char to make it a string!
    wifi_command_str[total_len] = '\0';

    printf(">> %s\n", wifi_command_str);

    putString_wifi(wifi_command_str);
    putString_wifi("\n");
}
