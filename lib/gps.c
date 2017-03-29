#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gps.h"
#include "wifi.h"
#include "touchscreen.h"
#include "../views/views.h"

void init_gps(void) {
	//set up 6850 control register to utilize a divide by 16 clock,
	//set RTS low, use 8 bits of data, no parity, 1 stop bit
	//transmitter interrupt disabled
	//program baud rate generator to use 9.6k baud
	GPS_CONTROL = 0x15;
	GPS_BAUD = 0x5;
}

// putchar_gps allows us to write 1 byte of data from the serial port.
int putchar_gps(char c) {
	//poll Tx bit in 6850 status register. Wait for it to become '1'
	//write 'c' to the 6850 TxData register to output the character

	while ((GPS_STATUS & 0x02) != 0x02)
		;
	GPS_TXDATA = c;
	return c;

}

// getchar_gps allows us to read 1 byte of data from the serial port.
char getchar_gps(void) {
	//poll Rx bit in 6850 status register. Wait for it to become '1'
	//read received character from 6850 register

	while (1) {
		if (GPS_STATUS & GPS_STATUS_RX_MASK) {
			return GPS_RXDATA;
		}
	}

	return (char) 0;
}

// test function to send a command via serial port, and begin printing
// output characters in the console.
void send_command(char *command) {

	int i;
	int length = strlen(command);

	//send the command to the gps
	for (i = 0; i < length; i++) {
		putchar_gps(command[i]);
	}
}

//Check when GPGGA is displayed
int check_GPGGA(void) {

	const char GPGGA[] = "$GPGGA";
	int length = strlen(GPGGA);
	char gps_output;
	int i;
	int check;

	for (i = 0; i < length; i++) {
		gps_output = getchar_gps();

		if (gps_output == GPGGA[i]) {

			check = 1;
			printf("%c", gps_output);

		} else {

			check = 0;
			break;
		}

	}

	return check;
}

//Converting NMEA to decimal degrees taken from:
//https://blog.encodez.com/blog/convert-nmea-latitude-longitude-to-decimal
double nmea2dec(char *nmea, char type, char *dir)
{
    int idx, dot = 0;
    double dec = 0;
    for (idx=0; idx<strlen(nmea);idx++){
        if (nmea[idx] == '.'){
            dot = idx;
            break;
        }
    }

    if (dot < 3)
        return 0;

    int dd;
    double mm;
    char cdd[5], cmm[10];
    memset(&cdd, 0, 5);
    memset(&cmm, 0, 10);
    strncpy(cdd, nmea, dot-2);
    strcpy(cmm, nmea+dot-2);
    dd = atoi(cdd);
    mm = atof(cmm);

    dec = dd + (mm/60);

    if (type == 1 && dec > MAX_LATITUDE)
        return 0;
    else if (type == 2 && dec > MAX_LONGITUDE)
        return 0;

    if (strcmp(dir, "N")== 0 || strcmp(dir, "E")== 0)
      return dec;
    else
      return -1 * dec;
}

//Read gps data from the gps module and print it to the console with the converted
// latitude and longitude
void read_gps_data(void) {
	int i;
	char start_log[] = "$PMTK622,1*29\r\n";

	int check = 0;
	int done = 0;
	int next = 0;
	char output = 0;
	char latitude[15] = {'\0'};
	char longitude[15] = {'\0'};
	char east_west[3] = {'\0'};
	char north_south[3] = {'\0'};
	char slat[50];
	char slong[50];
	double d_latitude;
	double d_longitude;

	send_command(start_log);

	while (done == 0) {

		if (check != 1) {
			while (check_GPGGA() != 1);
			check = 1;
			printf("\n");
		}

		else {

			output = getchar_gps();

			if (output == '*') {

				printf("Latitude (ddmm.mmmm): %s\n", latitude);
				printf("N/S Indicator: %s\n", north_south);
				printf("Longitude (dddmm.mmmm): %s\n", longitude);
				printf("E/W Indicator: %s\n", east_west);

				d_latitude = nmea2dec(latitude, '1', north_south);
				d_longitude = nmea2dec(longitude, '0', east_west);

				printf("THE LATITUDE IN DEGREE: %lf\n", d_latitude);
				printf("THE LONGITUDE IN DEGREE: %lf\n", d_longitude);

				done++;

			} else if (output == ',') {
				next++;
				i = 0;
			} else {
				if (next == LATITUDE) {
					latitude[i] = output;
				} else if (next == NORTH_SOUTH) {
					north_south[i] = output;
				} else if (next == LONGITUDE) {
					longitude[i] = output;
				} else if (next == EAST_WEST) {
					east_west[i] = output;
				}
				i++;
			}

		}
	}

	sprintf(slat,"%.5f", d_latitude);
	sprintf(slong, "%.5f", d_longitude);

	drawGPSData(slong, slat);
	WIFI_sendCoordinates(slat, slong);
}
