#define WIFI_CONTROL (*(volatile unsigned char *)(0x84000240))
#define WIFI_STATUS  (*(volatile unsigned char *)(0x84000240))
#define WIFI_TXDATA  (*(volatile unsigned char *)(0x84000242))
#define WIFI_RXDATA  (*(volatile unsigned char *)(0x84000242))
#define WIFI_BAUD    (*(volatile unsigned char *)(0x84000244))

#define WIFI_STATUS_TX_MASK 0x02
#define WIFI_STATUS_RX_MASK 0x01

void init_wifi(void);
void wait_for_read_ready();
void putchar_wifi(char c);
void putString_wifi(char *s);
char getchar_wifi(void);
