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
#include"interrupt_config.h"

// Datasheet'de interruptlar?n geri donus degeri void ve 
// keyword ise __interrupt() seklindedir.sonra interrupt ismi ve fonk.parantezi
// INTCONbits.INTF interrupt flag bitidir RB0 harici kesmesi 
// aktif olursa bu flag = 1 olmazsa flag = 0 olur.


void __interrupt() inteRB0(){   
    if(INTCONbits.INTF){        
        PORTBbits.RB7 = 1; 
        
        // Eger INTCONbits.INTF = 1 ise RB7 deki ledi 5 sn yakar 
        // sonra led sondurulup flag = 0 yapilmali ki surekli interrupt'a
        // girmesin interrupt bittigini anlasin.
        // Eger yapilmazsa,bir kere olduktan sonra bu flag kendisi 0 olmaz ve hep kesme olusur
        
        __delay_ms(5000);       
    }
    PORTBbits.RB7 = 0;
    INTCONbits.INTF = 0;
}

int main() {
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB7 = 0;
    PORTB = 0x00;
    
    ei_ex_rising();
    
    while(1){
        PORTBbits.RB1 =~ PORTBbits.RB1;
        __delay_ms(3000);
    }
}
