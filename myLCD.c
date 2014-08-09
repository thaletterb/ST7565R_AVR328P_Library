/*
$Id:$

ST7565 LCD library!

8 bit parallel mode
Data lines D0[0:7] connected to PORTD[0:7]
Control lines connected to PORTC[0:4]
3 Normally Open Buttons Connected to PORTB

*/

#include <avr/io.h>
#include <avr/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "lcdLibrary.h"
//#include "myFont.h"                // My font definitions

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

// my function prototypes
void clear_page(uint8_t page);
void update_time(void); 
void poll_buttons(void);
void setup_clock(void);
void loop(void);
void draw_screen(void);
void draw_clock(uint8_t setup); 
void draw_buttons(void); 

int main(void){
    lcd_initialize();
    while(1){
        loop();
    }
}

void loop(void){
    lcd_draw_string(0,0, "Hello World");
    lcd_draw_string(0,7, "Elegant Circuits");
    //disp();
    _delay_ms(1000);
}

void clear_page(uint8_t page){
    unsigned char count, msb, lsb;
    lsb = ((0)&(0x0F));
    msb = ((0>>4)&(0x0F));
    msb |= 0x10;
    page |= 0xB0;

    lcd_comm_out(msb);
    lcd_comm_out(lsb);
    lcd_comm_out(page);
    
    for (count=0;count<128;count++)//each character is 8 px tall
    {
        lcd_data_out(0x00);
    }
}
void disp()
{
    unsigned int i, j;
    unsigned char page=0xB0;
    for(i=0;i<8;i++)           //fill display with checkerboard pattern
    {
            lcd_comm_out(0x10);        //set column address
            lcd_comm_out(0x00);        //set column address
            lcd_comm_out(page);        //set page address
            for(j=0;j<64;j++)
            {
               lcd_data_out(0xAA);
               lcd_data_out(0x55);
            }
            page++;
    }
}
