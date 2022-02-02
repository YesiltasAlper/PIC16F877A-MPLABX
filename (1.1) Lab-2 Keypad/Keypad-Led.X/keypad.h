

#ifndef KEYPAD_H
#define	KEYPAD_H

#include <xc.h>

#define     Column1     PORTBbits.RB0 
#define     Column2     PORTBbits.RB1 
#define     Column3     PORTBbits.RB2 
#define     Row1        PORTBbits.RB3  
#define     Row2        PORTBbits.RB4 
#define     Row3        PORTBbits.RB5 
#define     Row4        PORTBbits.RB6 

#define     High        1
#define     Low         0

unsigned char keypad();

#endif	/* KEYPAD_H */

