#define BLUETOOTH_CONTROL (*(volatile unsigned char *)(0x84000220))
#define BLUETOOTH_STATUS  (*(volatile unsigned char *)(0x84000220))
#define BLUETOOTH_TXDATA  (*(volatile unsigned char *)(0x84000222))
#define BLUETOOTH_RXDATA  (*(volatile unsigned char *)(0x84000222))
#define BLUETOOTH_BAUD    (*(volatile unsigned char *)(0x84000224))
#define BLUETOOTH_STATUS_TX_MASK 0x02
#define BLUETOOTH_STATUS_RX_MASK 0x01

#define BLUETOOTH_COMMAND_DELAY 2 * 1000 * 1000 // Set to 2s
#define BLUETOOTH_STRING_BUFFER_SIZE 50

// SERIAL-PORT FUNCTIONS
void BLUETOOTH_init();
void BLUETOOTH_putChar(char c);
void BLUETOOTH_putString(char *s);
void BLUETOOTH_waitForReadReady();
char BLUETOOTH_getChar();
int  BLUETOOTH_getString(char *str_buffer, int buflen);

// BLUETOOTH [MODE-SWITCHING] FUNCTIONS
void BLUETOOTH_enterCommandMode();
void BLUETOOTH_exitCommandMode();

// BLUETOOTH [COMMAND] FUNCTIONS
void BLUETOOTH_setDeviceName();
void BLUETOOTH_setDevicePin();
void BLUETOOTH_factoryReset();

// BLUETOOTH [TEST] FUNCTIONS
void BLUETOOTH_testSerialPorts();
void BLUETOOTH_configureModule();
