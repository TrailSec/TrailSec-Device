#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../lib/wifi.h"
#include "wifi_commands.h"

void
WIFI_sendCoordinates(char *latitude, char *longitude) {

    int i, total_len = 0;

  	char wifi_command_str[100] = "";
  	char str0[] = "send_coor(\"";
  	char str2[] = "\", \"";
  	char str3[] = "\")";

    // send_coor(\"
  	for (i = 0; str0[i] != '\0'; i++, total_len++)
  		wifi_command_str[total_len] = str0[i];

    // send_coor(\"XX.XXXX
  	for (i = 0; latitude[i] != '\0'; i++, total_len++)
  		wifi_command_str[total_len] = latitude[i];

    // send_coor(\"XX.XXXX\", \"
  	for (i = 0; str2[i] != '\0'; i++, total_len++)
  		wifi_command_str[total_len] = str2[i];

    // send_coor(\"XX.XXXX\", \"YY.YYYY
  	for (i = 0; longitude[i] != '\0'; i++, total_len++)
  		wifi_command_str[total_len] = longitude[i];

    // send_coor(\"XX.XXXX\", \"YY.YYYY\")
  	for (i = 0; str3[i] != '\0'; i++, total_len++)
  		wifi_command_str[total_len] = str3[i];

    // Append NULL-char to make it a string!
  	wifi_command_str[total_len] = '\0';

    printf(">> %s\n", wifi_command_str);

  	putString_wifi(wifi_command_str);
  	putString_wifi("\n");
}
