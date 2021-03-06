#ifndef PORTS
#define PORTS
#include "C8051F120.h"
//DACs

sfr16 DAC0  = 0xd2;  // DAC0 data
sfr16 DAC1  = 0xd2;  // DAC1 data

//ADC Timers

sfr16 ADC0     = 0xbe;                 // ADC0 data
sfr16 RCAP2    = 0xca;                 // Timer2 capture/reload
sfr16 RCAP3    = 0xca;                 // Timer3 capture/reload
sfr16 TMR2     = 0xcc;                 // Timer2
sfr16 TMR3     = 0xcc;                 // Timer3

//Port 0
sbit MEM_SDA = P0^2; //SDA MEM
sbit MEM_SSL = P0^3; //SCL MEM
sbit MEM_WP  = P0^7; //WP MEM

//Port 1
sbit LCD_DI = P1^0; //data and instruction LCD pin
sbit LCD_RW = P1^1; //read and write LCD pin
sbit LCD_EN = P1^2; //enable LCD pin
sbit LCDRST = P1^3; //reset LCD active HI work LOW

//Port 2
//Data for LCD

//Port 3
sbit ENC_A 	= P3^0;
sbit ENC_C 	= P3^1;
sbit ENC_SW = P3^2;
sbit SW_1	= P3^3;
sbit SW_2	= P3^4;
sbit SW_3	= P3^5;
sbit SW_4 	= P3^6;
sbit LCDBLT = P3^7; //backlight LCD active LOW and need enable output data port OUT_LE to HI

//

#endif