#include "lcd.h"
#include "C8051F120.h"
#include "ports.h"


//============================================================================
//============================================================================
void write_command(unsigned char ldata)
{
  P2 = ldata;
  LCD_DI = 0; //DI = 0
  LCD_RW = 0; //RW = 0
  LCD_EN = 1;  //EN = 1
  LCD_EN = 0;  //EN = 0
  _delay_us(850);
  LCD_EN = 1;  //EN = 1
}
//----------------------------------------------------------------------------
void write_data(unsigned char ldata)
{
  P2 = ldata;
  LCD_DI = 1; //DI = 1
  LCD_RW = 0; //RW = 0
  LCD_EN = 1;  //EN = 1
  LCD_EN = 0;	//EN = 0
  _delay_us(850);
  LCD_EN = 1;	//EN = 1
}
//----------------------------------------------------------------------------
void write_data_16(unsigned int ldata)
{
  P2 = ldata>>8;
	
  LCD_DI = 1;	//DI = 1
  LCD_RW = 1;	//RW = 1
  LCD_EN = 1;	//EN = 1
  LCD_EN = 0;	//EN = 0
  _delay_us(850);
  LCD_EN = 1;	//EN = 1
  P2 = ldata;
  LCD_EN = 0;	//EN = 0
  _delay_us(850);
  LCD_EN = 1;	//EN = 1
}
//----------------------------------------------------------------------------
void Clear_LCD(void)
{
	write_command(0x38);
	write_command(0x38);
	write_command(0x38);
    write_command(0x38);	// установить 8-ми битный режим
    write_command(0x0A);  	// cursor on
    write_command(0x01);	// очистка дисплея
    write_command(0x06); 	// 0x06 курсор вправо, 0x04 курсор влево
    //write_command(0x0F);	// включить курсор и мигать
    write_command(0x0B);
	write_command(0x01);	// очистка дисплея

}
//----------------------------------------------------------------------------
//
void Write_Char (unsigned char pos, unsigned char ldata)
{
	write_command(0x14);
	write_command(0x14);
	write_command(0x14);
	write_command(0x80+pos);
	write_data(ldata);		
}
//============================================================================
void ResetLCD(void)
{
     LCDRST = 0; //RST = 0
    	_delay_us(6500);
		_delay_us(6500);    
		_delay_us(6500);
		_delay_us(6500);
		_delay_us(6500);
		_delay_us(6500);
     LCDRST = 1; //RST = 1
}

//============================================================================
void InitializeLCD(void)
{
	/* Take the LCD out of reset (if reset was low)
	*/
	LCDRST = 1; //RST = 1

	_delay_us(6500);

	//Display on
	write_command(0x30); //8 bit
	write_command(0x0F); //On and blink cursor
	write_command(0x30); //8 bit
	write_command(0x01); //clear scr
	write_command(0x06); //direct cursor
	//write_command(0x32);
	//write_command(0x36);

}
//============================================================================
void _delay_us(int ms)
{
	int i;
	while (ms>0){
		for (i = 3; i > 0; i--);
		ms--;
	}
}