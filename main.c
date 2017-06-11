
#include "init.h"
#include "lcd.h"
#include "encoder.h"
#include <stdio.h>


void ADC0_ISR (void);

long Result;                           // ADC0 decimated value

void main(){
	int i, encspin;
	long v, a;
	char SFRPAGE_SAVE = SFRPAGE;
	Reset_Sources_Init();
  	//Timer_Init();
  	SMBus_Init();
  	DAC_Init();
	Voltage_Reference_Init();
  	Port_IO_Init();
  	Oscillator_Init();
 
	LCDBLT  = 1; //Backlight LCD Off

	InitializeLCD();

   	SFRPAGE = DAC0_PAGE;
   	DAC0 = 0xB200;           // Write to DAC0

   	SFRPAGE = DAC1_PAGE;
   	DAC1 = 0x2FF0;           // Write to DAC1
   
   	SFRPAGE = SFRPAGE_SAVE;             // Restore SFR page


	LCDBLT = 0; //Backlight LCD On

	//Clear_LCD();
	Write_Char(0, 'V');
//	Write_Char(1, '0');
//	Write_Char(2, '3');
//	Write_Char(3, ',');
//	Write_Char(4, '3');
	Write_Char(16, '[');
//	Write_Char(17, '0');
//	Write_Char(18, '3');
//	Write_Char(19, ',');
//	Write_Char(20, '3');
	Write_Char(21, ']');
	Write_Char(8, 'A');
//	Write_Char(9, '0');
//	Write_Char(10, ',');
//	Write_Char(11, '5');
//	Write_Char(12, '1');
	Write_Char(24, '[');
//	Write_Char(25, '0');
//	Write_Char(26, ',');
//	Write_Char(27, '9');
//	Write_Char(28, '9');
	Write_Char(29, ']');
	Write_Char(30, ' ');


//	show_text();


   TIMER3_Init (SYSCLK/SAMPLE_RATE);   // Initialize Timer3 to overflow at


	while(1){

		_delay_us(80);
		if (0 == ENC_PollEncoder()){
			encspin = ENC_GetStateEncoder();	
		}
		if (encspin == 1){
			Write_Char(1, '+');
		}else{
			Write_Char(1, '-');
		}

	}
}



//-----------------------------------------------------------------------------
// Interrupt Service Routines
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// ADC0_ISR
//-----------------------------------------------------------------------------
//
// Here we take the ADC0 sample, add it to a running total <accumulator>, and
// decrement our local decimation counter <int_dec>.  When <int_dec> reaches
// zero, we post the decimated result in the global variable <Result>.
//
//-----------------------------------------------------------------------------
void ADC0_ISR (void) interrupt 15
{
   static unsigned int_dec=INT_DEC;    // Integrate/decimate counter
                                       // we post a new result when
                                       // int_dec = 0
   static long accumulator=0L;         // Here's where we integrate the
                                       // ADC samples

   AD0INT = 0;                         // Clear ADC conversion complete
                                       // indicator

   accumulator += ADC0;                // Read ADC value and add to running
                                       // total
   int_dec--;                          // Update decimation counter

   if (int_dec == 0)                   // If zero, then post result
   {
      int_dec = INT_DEC;               // Reset counter
      Result = accumulator >> 8;
      accumulator = 0L;                // Reset accumulator
   }
}



