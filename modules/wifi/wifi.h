#define WIFI_CONTROL (*(volatile unsigned char *)(0x84000240))
#define WIFI_STATUS  (*(volatile unsigned char *)(0x84000240))
#define WIFI_TXDATA  (*(volatile unsigned char *)(0x84000242))
#define WIFI_RXDATA  (*(volatile unsigned char *)(0x84000242))
#define WIFI_BAUD    (*(volatile unsigned char *)(0x84000244))
#define WIFI_STATUS_TX_MASK 0x02
#define WIFI_STATUS_RX_MASK 0x01

void WIFI_init(void);
void WIFI_waitForReadReady();
void WIFI_putChar(char c);
void WIFI_putString(char *s);
char WIFI_putChar(void);

void WIFI_sendCoordinates(char *latitude, char *longitude, char *user_id);
