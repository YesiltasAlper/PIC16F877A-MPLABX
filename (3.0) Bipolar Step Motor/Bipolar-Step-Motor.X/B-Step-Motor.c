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

int i = 0;
int yarim_adim[]={1,3,2,6,4,12,8,9};

void main() {
    
    TRISB=0x00;
    PORTB = 0x00;
    
    while(1){
        
         PORTB = yarim_adim[i];
        __delay_ms(1500);
        i++;

        if(i == 8){
            i = 0;
            __delay_ms(1500);
        }
 
    }
}
