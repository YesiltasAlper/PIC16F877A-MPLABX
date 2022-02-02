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

int main() {
          
    TRISCbits.TRISC2 = 0;   
    PORTC = 0x00;
    
    INTCONbits.GIE = 1;     // tum interruptlara izin
    INTCONbits.PEIE = 1;	// TMR2'ye izin vermek icin PEIE acilmalidir cunku TMR1 ve TMR2 Peripheral'da bulunur
    
    PIR1bits.TMR2IF = 0;    // TMR2 to PR2 Match Interrupt Flag bit clear edildi ilk basta
    
    PIE1bits.TMR2IE = 1;    // TMR2 kesmesine izin verildi
    
    T2CONbits.TMR2ON = 1;   // TMR2 aktif
    
    T2CONbits.T2CKPS0 = 1;  // Bunlar Timer2 bolme orani ayarlama bitleri
    T2CONbits.T2CKPS1 = 0;  // burada bolme orani 4 ayarlandi
    
    CCP1CONbits.CCP1M2 = 1; // CCP PWM modu aktif
    CCP1CONbits.CCP1M3 = 1; // edildi bu iki kodla
    
    PR2 = 249;
    CCPR1L = 125;
    
    while(1){
    }
}

