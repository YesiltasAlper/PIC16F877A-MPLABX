#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#define     _XTAL_FREQ       4000000

int counter=0,step=3;
int gecikme=0;

void __interrupt() KESME(void){
    
if(T0IF){
    
    gecikme++;

    if(gecikme>5000){

        gecikme=0;

        if(step>8){
            step=2;
        }
        step++;
    }

    counter++;

    if (counter<=step)
        RB0=1;
    else if (counter>step)
        RB0=0;

   if (counter==100)
        counter=0;
}
    TMR0=231;
    T0IF=0;
}


void main() {
     
    GIE=1;
    T0IE=1;
    TRISB=0;
    OPTION_REG=0x02;
    TMR0=231;
    while(1){}
}