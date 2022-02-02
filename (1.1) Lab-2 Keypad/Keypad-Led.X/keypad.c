#include "keypad.h"
#include <xc.h>
#define     _XTAL_FREQ       4000000

unsigned char keypad(){

    unsigned char key;
    
    Column1 = High;
    if(Row1 == High)    {__delay_ms(20);  key = 1;}
    if(Row2 == High)    {__delay_ms(20);  key = 4;}
    if(Row3 == High)    {__delay_ms(20);  key = 7;}
    if(Row4 == High)    {__delay_ms(20);  key = 15;}
    Column1 = Low;
    
    Column2 = High;
    if(Row1 == High)    {__delay_ms(20);  key = 2;}
    if(Row2 == High)    {__delay_ms(20);  key = 5;}
    if(Row3 == High)    {__delay_ms(20);  key = 8;}
    if(Row4 == High)    {__delay_ms(20);  key = 0;}
    Column2 = Low;
    
    Column3 = High;
    if(Row1 == High)    {__delay_ms(20);  key = 3;}
    if(Row2 == High)    {__delay_ms(20);  key = 6;}
    if(Row3 == High)    {__delay_ms(20);  key = 9;}
    if(Row4 == High)    {__delay_ms(20);  key = 255;}
    Column3 = Low;
    
    return key;
}
