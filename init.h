/////////////////////////////////////
//  Generated Initialization File  //
/////////////////////////////////////

#include "ports.h"


#define BAUDRATE     115200            // Baud rate of UART in bps
#define SYSCLK       48000000          // Output of PLL derived from (INTCLK*2)
#define SAMPLE_RATE  50000             // Sample frequency in Hz
#define INT_DEC      256               // Integrate and decimate ratio
#define SAR_CLK      2500000           // Desired SAR clock speed

#define SAMPLE_DELAY 50                // Delay in ms before taking sample



// Peripheral specific initialization functions,
// Called from the Init_Device() function
void Reset_Sources_Init()
{
    WDTCN     = 0xDE;
    WDTCN     = 0xAD;
}

void Timer_Init()
{
    SFRPAGE   = TIMER01_PAGE;
    TMOD      = 0x20;
    CKCON     = 0x01;
    TH1       = 0x45;
    SFRPAGE   = TMR2_PAGE;
    TMR2CF    = 0x08;
    RCAP2L    = 0xFA;
    RCAP2H    = 0xFF;
}



void SMBus_Init()
{
    SFRPAGE   = SMB0_PAGE;
    SMB0CN    = 0x40;
}

void DAC_Init()
{
    SFRPAGE   = DAC0_PAGE;
    DAC0CN    = 0x81;
    SFRPAGE   = DAC1_PAGE;
    DAC1CN    = 0x81;
}

void Voltage_Reference_Init()
{
    SFRPAGE   = ADC0_PAGE;
    REF0CN    = 0x03;
}

void Port_IO_Init()
{
    // P0.0  -  TX0 (UART0), Push-Pull,  Digital
    // P0.1  -  RX0 (UART0), Push-Pull,  Digital
    // P0.2  -  SDA (SMBus), Push-Pull,  Digital
    // P0.3  -  SCL (SMBus), Push-Pull,  Digital
    // P0.4  -  T0 (Timer0), Push-Pull,  Digital
    // P0.5  -  T1 (Timer1), Push-Pull,  Digital
    // P0.6  -  T2 (Timer2), Push-Pull,  Digital
    // P0.7  -  T4 (Timer4), Push-Pull,  Digital

    // P1.0  -  Unassigned,  Push-Pull,  Digital
    // P1.1  -  Unassigned,  Push-Pull,  Digital
    // P1.2  -  Unassigned,  Push-Pull,  Digital
    // P1.3  -  Unassigned,  Push-Pull,  Digital
    // P1.4  -  Unassigned,  Push-Pull,  Digital
    // P1.5  -  Unassigned,  Push-Pull,  Digital
    // P1.6  -  Unassigned,  Push-Pull,  Digital
    // P1.7  -  Unassigned,  Push-Pull,  Digital

    // P2.0  -  Unassigned,  Push-Pull,  Digital
    // P2.1  -  Unassigned,  Push-Pull,  Digital
    // P2.2  -  Unassigned,  Push-Pull,  Digital
    // P2.3  -  Unassigned,  Push-Pull,  Digital
    // P2.4  -  Unassigned,  Push-Pull,  Digital
    // P2.5  -  Unassigned,  Push-Pull,  Digital
    // P2.6  -  Unassigned,  Push-Pull,  Digital
    // P2.7  -  Unassigned,  Push-Pull,  Digital

    // P3.0  -  Unassigned,  Open-Drain, Digital
    // P3.1  -  Unassigned,  Open-Drain, Digital
    // P3.2  -  Unassigned,  Open-Drain, Digital
    // P3.3  -  Unassigned,  Open-Drain, Digital
    // P3.4  -  Unassigned,  Open-Drain, Digital
    // P3.5  -  Unassigned,  Open-Drain, Digital
    // P3.6  -  Unassigned,  Open-Drain, Digital
    // P3.7  -  Unassigned,  Push-Pull,  Digital

    SFRPAGE   = CONFIG_PAGE;
    P0MDOUT   = 0xFF;
    P1MDOUT   = 0xFF;
    P2MDOUT   = 0xFF;
    P3MDOUT   = 0x80;
    XBR0      = 0x05;
    XBR1      = 0x2A;
    XBR2      = 0x48;
}

void Oscillator_Init()
{
    int i = 0;
    SFRPAGE   = CONFIG_PAGE;
    OSCXCN    = 0x67;
    for (i = 0; i < 3000; i++);  // Wait 1ms for initialization
    while ((OSCXCN & 0x80) == 0);
    PLL0CN    = 0x04;
    CCH0CN    &= ~0x20;
    SFRPAGE   = LEGACY_PAGE;
    FLSCL     = 0x90;
    SFRPAGE   = CONFIG_PAGE;
    CCH0CN    |= 0x20;
    PLL0CN    |= 0x01;
    PLL0DIV   = 0x01;
    PLL0FLT   = 0x21;
    PLL0MUL   = 0x02;
    for (i = 0; i < 15; i++);  // Wait 5us for initialization
    PLL0CN    |= 0x02;
    while ((PLL0CN & 0x10) == 0);
    CLKSEL    = 0x02;
    OSCICN    &= ~0x80;
}

//-----------------------------------------------------------------------------
// ADC0_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// Configure ADC0 to use Timer3 overflows as conversion source, to
// generate an interrupt on conversion complete, and to use right-justified
// output mode.  Enables ADC end of conversion interrupt. Leaves ADC disabled.
//
//-----------------------------------------------------------------------------
void ADC0_Init (void)
{
   char SFRPAGE_SAVE = SFRPAGE;        // Save Current SFR page

   SFRPAGE = ADC0_PAGE;

   ADC0CN = 0x04;                      // ADC0 disabled; normal tracking
                                       // mode; ADC0 conversions are initiated
                                       // on overflow of Timer3; ADC0 data is
                                       // right-justified

   REF0CN = 0x07;                      // Enable temp sensor, on-chip VREF,
                                       // and VREF output buffer

   AMX0CF = 0x00;                      // AIN inputs are single-ended (default)

   AMX0SL = 0x01;                      // Select AIN0.1 pin as ADC mux input

   ADC0CF = (SYSCLK/SAR_CLK) << 3;     // ADC conversion clock = 2.5MHz
   ADC0CF |= 0x00;                     // PGA gain = 1 (default)

   EIE2 |= 0x02;                       // enable ADC interrupts

   SFRPAGE = SFRPAGE_SAVE;             // Restore SFR page
}

//-----------------------------------------------------------------------------
// TIMER3_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   :
//   1)  int counts - calculated Timer overflow rate
//                    range is postive range of integer: 0 to 32767
//
// Configure Timer3 to auto-reload at interval specified by <counts> (no
// interrupt generated) using SYSCLK as its time base.
//
//-----------------------------------------------------------------------------
void TIMER3_Init (int counts)
{
   char SFRPAGE_SAVE = SFRPAGE;        // Save Current SFR page

   SFRPAGE = TMR3_PAGE;

   TMR3CN = 0x00;                      // Stop Timer3; Clear TF3;
   TMR3CF = 0x08;                      // use SYSCLK as timebase

   RCAP3   = -counts;                  // Init reload values
   TMR3    = RCAP3;                    // Set to reload immediately
   EIE2   &= ~0x01;                    // Disable Timer3 interrupts
   TR3     = 1;                        // start Timer3

   SFRPAGE = SFRPAGE_SAVE;             // Restore SFR page
}

//-----------------------------------------------------------------------------
// Wait_MS
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters:
//   1) unsigned int ms - number of milliseconds of delay
//                        range is full range of integer: 0 to 65335
//
// This routine inserts a delay of <ms> milliseconds.
//
//-----------------------------------------------------------------------------
void Wait_MS(unsigned int ms)
{
   char SFRPAGE_SAVE = SFRPAGE;        // Save Current SFR page

   SFRPAGE = TMR2_PAGE;

   TMR2CN = 0x00;                      // Stop Timer3; Clear TF3;
   TMR2CF = 0x00;                      // use SYSCLK/12 as timebase

   RCAP2 = -(SYSCLK/1000/12);          // Timer 2 overflows at 1 kHz
   TMR2 = RCAP2;

   ET2 = 0;                            // Disable Timer 2 interrupts

   TR2 = 1;                            // Start Timer 2

   while(ms)
   {
      TF2 = 0;                         // Clear flag to initialize
      while(!TF2);                     // Wait until timer overflows
      ms--;                            // Decrement ms
   }

   TR2 = 0;                            // Stop Timer 2

   SFRPAGE = SFRPAGE_SAVE;             // Restore SFRPAGE
}

