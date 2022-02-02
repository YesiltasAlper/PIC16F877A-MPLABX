#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#include "portb_interrupt_config.h"
#define     _XTAL_FREQ       4000000

void __interrupt() portB_inter(){
    PORTB = 0x00;
    
    if((INTCONbits.RBIF) && (PORTBbits.RB4)){                 
        PORTBbits.RB0 = 1;
        __delay_ms(3000);
    }
    
    else if((INTCONbits.RBIF) && (PORTBbits.RB5)){             
        PORTBbits.RB1 = 1;
        __delay_ms(3000);
    }
    
    else if((INTCONbits.RBIF) && (PORTBbits.RB6)){              
        PORTBbits.RB2 = 1;
        __delay_ms(3000);
    }
    
    else if((INTCONbits.RBIF) && (PORTBbits.RB7)){          
        PORTBbits.RB0 = 1;  
        PORTBbits.RB1 = 1;
        PORTBbits.RB2 = 1;
        __delay_ms(3000);
    }
    
    INTCONbits.RBIF = 0;    // PORTB interrupt flag bit
}


int main() {
    
    PORTB=0x00;     // PortB sifirlandi
    TRISB = 0xF0;   // ilk 4 pin cikis son 4 pin giris
    ei_portb();     // PORTB interrupt configuration settings
    
    while(1){
        PORTBbits.RB1 = 1;
        PORTBbits.RB2 = 1;
    }
}
