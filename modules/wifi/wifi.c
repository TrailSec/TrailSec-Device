#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "wifi.h"

void WIFI_init(void)
{
    WIFI_CONTROL = 0x15;
    WIFI_BAUD = 0x01;
    WIFI_putString("\n");
    usleep(1000);
    WIFI_putString("\n");
    WIFI_putString("dofile(\"trailsec.lua\")");
    WIFI_putString("\n");
}

// Blocks the serial port until it is ready
void WIFI_waitForReadReady()
{
    while((WIFI_STATUS & WIFI_STATUS_RX_MASK) != WIFI_STATUS_RX_MASK);
}

// Write 1 byte of data into the WIFI serial port
void WIFI_putChar(char c)
{
    while ((WIFI_STATUS & WIFI_STATUS_TX_MASK) != WIFI_STATUS_TX_MASK);
    WIFI_TXDATA = c & 0xFF;
}

// Write a string into the wifi TX port
void WIFI_putString(char *s)
{
    int i;
    for(i=0; s[i]!='\0'; i++){
        WIFI_putChar((char) s[i]);
    }
}

char WIFI_putChar(void)
{
    WIFI_waitForReadReady();
    return WIFI_RXDATA;
}

void WIFI_sendCoordinates(char *latitude, char *longitude, char *user_id) {

    printf(">> SENDING...\n");

    int i, total_len = 0;

    char wifi_command_str[150] = "";
    char str0[] = "POST_TO_FIREBASE(\"";
    char str2[] = "\", \"";
    char str3[] = "\")";

    // POST_TO_FIREBASE(\"
    for (i = 0; str0[i] != '\0'; i++, total_len++) {
        wifi_command_str[total_len] = str0[i];
    }

    // POST_TO_FIREBASE(\"XX.XXXX
    for (i = 0; latitude[i] != '\0'; i++, total_len++) {
        wifi_command_str[total_len] = latitude[i];
    }

    // POST_TO_FIREBASE(\"XX.XXXX\", \"
    for (i = 0; str2[i] != '\0'; i++, total_len++) {
        wifi_command_str[total_len] = str2[i];
    }

    // POST_TO_FIREBASE(\"XX.XXXX\", \"YY.YYYY
    for (i = 0; longitude[i] != '\0'; i++, total_len++) {
        wifi_command_str[total_len] = longitude[i];
    }

    // POST_TO_FIREBASE(\"XX.XXXX\", \"YY.YYYY\", \"
    for (i = 0; str2[i] != '\0'; i++, total_len++) {
        wifi_command_str[total_len] = str2[i];
    }

    // POST_TO_FIREBASE(\"XX.XXXX\", \"YY.YYYY\", \"ZZZZZZZZZZZZ
    for (i = 0; user_id[i] != '\0'; i++, total_len++) {
        wifi_command_str[total_len] = user_id[i];
    }

    // POST_TO_FIREBASE(\"XX.XXXX\", \"YY.YYYY\", \"ZZZZZZZZZZZZ\")
    for (i = 0; str3[i] != '\0'; i++, total_len++) {
        wifi_command_str[total_len] = str3[i];
    }

    // Append NULL-char to make it a string!
    wifi_command_str[total_len] = '\0';

    printf(">> %s\n", wifi_command_str);

    WIFI_putString(wifi_command_str);
    WIFI_putString("\n");
}
