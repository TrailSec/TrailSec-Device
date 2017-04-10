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

void GPS_init(void);
int  GPS_putChar(char c);
void GPS_putString(char *s);
char GPS_getChar(void);
int  GPS_checkSequence(void);
void GPS_getCoordinates(double *d_latitude, double *d_longitude);
double GPS_NMEA2DEC(char *nmea, char type, char *dir);
