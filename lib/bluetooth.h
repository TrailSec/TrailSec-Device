#define BLUETOOTH_CONTROL (*(volatile unsigned char *)(0x84000220))
#define BLUETOOTH_STATUS  (*(volatile unsigned char *)(0x84000220))
#define BLUETOOTH_TXDATA  (*(volatile unsigned char *)(0x84000222))
#define BLUETOOTH_RXDATA  (*(volatile unsigned char *)(0x84000222))
#define BLUETOOTH_BAUD    (*(volatile unsigned char *)(0x84000224))
#define BLUETOOTH_STATUS_TX_MASK 0x02
#define BLUETOOTH_STATUS_RX_MASK 0x01

#define BLUETOOTH_COMMAND_DELAY 2000000 // Set to 2s

// SERIAL-PORT FUNCTIONS
void init_bluetooth();
void putchar_bluetooth(char c);
void putString_bluetooth(char *s);
void wait_for_read_ready_bluetooth();
char getchar_bluetooth();
int getCommand_bluetooth(char *str_buffer, int buflen);

// BLUETOOTH [MODE-SWITCHING] FUNCTIONS
void enter_command_mode();
void exit_command_mode();

// BLUETOOTH [COMMAND] FUNCTIONS
void set_device_name();
void set_device_pin();
void reset_to_factory_defaults();

// BLUETOOTH [TEST] FUNCTIONS
void test_bluetooth_serial_ports();
void configure_bluetooth_dongle();
