// Define Control Pins on PORTC 
#define LCD_CONTROL_PORT PORTC
#define LCD_CONTROL_PIN PINC
#define LCD_CONTROL_DDR DDRC
#define CS1 0
#define RES 1
#define A0 2
#define WR 3
#define RD 4

// Define Button Pins on PORTB
#define DEVICE_CONTROL_PORT PORTB
#define DEVICE_CONTROL_PIN PINB
#define DEVICE_CONTROL_DDR DDRB
#define SETUP 0
#define START 1
#define DISPLAY 2

void lcd_draw_char(unsigned char column, unsigned char page, unsigned char letter);
void lcd_draw_string(uint8_t column, uint8_t page, char *string);
void lcd_initialize(void);
void lcd_comm_out(uint8_t c);
void lcd_data_out(uint8_t d);
