#ifndef	encoder_h
#define	encoder_h

#include "ports.h"

//______________________
#define RIGHT_SPIN 0x01 
#define LEFT_SPIN 0xff

unsigned char ENC_PollEncoder(void);
unsigned char ENC_GetStateEncoder(void);
#endif  //encoder_h
