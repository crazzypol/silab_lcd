#ifndef LCD
#define LCD

void ResetLCD(void);
void InitializeLCD(void);
void Clear_LCD(void);
void Write_Char (unsigned char, unsigned char);
void _delay_us(int);

#endif