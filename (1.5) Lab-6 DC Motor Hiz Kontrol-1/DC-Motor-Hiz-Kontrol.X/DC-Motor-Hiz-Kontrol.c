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

int duty1 = 0;
int duty2 = 0;

void __interrupt()kesme(){
    
    if(RBIF){
        
        RBIE = 0;
        if(RB4 == 1 && duty1 < 1000){
            duty1 = duty1 + 100;
        }
        if(RB5 == 1 && duty1 > 0){
            duty1 = duty1 - 100;
        }
        if(RB6 == 1 && duty2 < 1000){
            duty2 = duty2+100;
        }
        if(RB7 == 1 && duty2 > 0){
            duty2 = duty2 - 100;
        }
    }
    RBIE = 1;
    RBIF = 0;
}

void main() {
    
    TRISB = 0xF0;
    TRISC = 0x00;
    TRISD = 0x0F;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    
    GIE = 1;
    PEIE = 1;
    RBIE = 1;
    RBIF = 0;
    
    CCP1CON = 0b00001111;   // Pwm1 ayari
    CCP2CON = 0b00001111;   // Pwm2 ayari
    T2CON = 0b00000111;     // T2 ON,Prescale 16
    
    TMR2 = 0;
    PR2 = 250;
    
    while(1){
    
        if(RD0 == 1){
            RB0 = 0;
            RB1 = 1;
        }
        if(RD0 == 0){
            RB0 = 1;
            RB1 = 0;
        }
        if(RD1 == 1){
            RB2 = 0;
            RB3 = 1;
        }
        if(RD1 == 0){
            RB2 = 1;
            RB3 = 0;
        }
        
        CCPR1L = duty1>>2;
        CCP1Y = duty1&1;
        CCP1X = duty1&2;
        
        CCPR2L = duty2>>2;
        CCP2Y = duty2&1;
        CCP2X = duty2&2;
    }
}
