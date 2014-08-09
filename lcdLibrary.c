/*
$Id:$
// lcdLibrary.c

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
#include "myFont.h"                // My font definitions
#include "lcdLibrary.h"

void lcd_draw_char(unsigned char column, unsigned char page, unsigned char letter){
    unsigned char count, msb, lsb;
    
    lsb = ((column)&(0x0F));
    msb = ((column>>4)&(0x0F));
    msb |= 0x10;
    page |= 0xB0;
    
    lcd_comm_out(msb);
    lcd_comm_out(lsb);
    lcd_comm_out(page);

    for (count=0;count<5;count++)//each character is 5px wide - 'count'
    {
        lcd_data_out(Ascii_1[letter][count]);
    }
}

void lcd_draw_string(uint8_t column, uint8_t page, char *string){
    uint8_t i = 0;
    while(string[0] != 0){
        lcd_draw_char(column+(5*i), page, (string[0]-32));
        string++;
        i++;
    }
}

void lcd_initialize(void){
    DDRC = 0xFF;                                // set PORTC (Control lines) as output
    PORTC = 0x00;                               // set PORTC Pins low
    DDRD = 0xFF;                                // set PORTD (Data Signals) as output
    PORTD = 0x00;                               // set PORTD Pins low

    DDRB |= ((1<<SETUP) | (1<<DISPLAY) | (1<<START));                         // set PORTB PIN0 as input (SETUP Button)
    PORTB |= ((1<<SETUP) | (1<<DISPLAY) | (1<<START));                        // enable pullup resistor

    PORTC |= ((1<<RD) | (1<<WR) | (0<<RES));    // Set RD, WR High, RES lines low
    _delay_ms(150);

    PORTC |=  (1<<RES);                         // now toggle RES high
    _delay_ms(150);

    lcd_comm_out(0xA2);                             // added 1/9 bias
    lcd_comm_out(0xA0);                             // ADC segment driver direction (A0 = normal)
    lcd_comm_out(0xC8);                             // COM output scan direction (C0 = normal/C8)
    lcd_comm_out(0x25);                             // resistor ratio
    lcd_comm_out(0x81);                             // electronic volume mode set
    lcd_comm_out(0x15);                             // electronic volume register set
    lcd_comm_out(0x2F);                             // operating mode
    lcd_comm_out(0x40);                             // start line set
    lcd_comm_out(0xAF);                             // display on

    _delay_ms(10);
}

void lcd_comm_out(uint8_t c){
    PORTC &= ~(1<<A0);       // set A0 (RS) low (Command)
    PORTC &= ~(1<<WR);       // set WR low
    PORTD = c;              // send command to PORTD data lines
    PORTC |= (1<<WR);       // set WR high 
}

void lcd_data_out(uint8_t d){
    PORTC |= (1<<A0);       // set A0 (RS) high (Data) 
    PORTC &= ~(1<<WR);       // set WR low
    PORTD = d;              // send command to PORTD data lines
    PORTC |= (1<<WR);       // set WR high 
}
