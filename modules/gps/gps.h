#define GPS_CONTROL (*(volatile unsigned char *)(0x84000210))
#define GPS_STATUS  (*(volatile unsigned char *)(0x84000210))
#define GPS_TXDATA  (*(volatile unsigned char *)(0x84000212))
#define GPS_RXDATA  (*(volatile unsigned char *)(0x84000212))
#define GPS_BAUD    (*(volatile unsigned char *)(0x84000214))
#define GPS_STATUS_TX_MASK 0x02
#define GPS_STATUS_RX_MASK 0x01

#define LATITUDE 2
#define NORTH_SOUTH 3
#define LONGITUDE 4
#define EAST_WEST 5

#define MAX_LONGITUDE    180
#define MAX_LATITUDE     90

void init_gps(void);
int putchar_gps(char c);
char getchar_gps(void);

void send_command(char *command);
int check_GPGGA(void);
double nmea2dec(char *nmea, char type, char *dir);
void read_gps_data(void);
