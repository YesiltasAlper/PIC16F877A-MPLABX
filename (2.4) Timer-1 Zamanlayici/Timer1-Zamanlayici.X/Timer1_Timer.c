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

void __interrupt()timer1_inter(){
    TMR1 = 45536;
    
    static unsigned int i = 0;
    
    if(PIR1bits.TMR1IF && i == 100){        // 100 kesme olustugunda = 2 sn gectiginde
        PORTBbits.RB0 = 1;
    }
    
    if(PIR1bits.TMR1IF && i == 200){       // 200 kesme olustugunda = 4 sn gectiginde
        PORTBbits.RB0 = 0;
        i = 0;
    }
    
    i++;
    PIR1bits.TMR1IF = 0;    // TMR1 flag biti 
}


int main() {
    PORTB = 0x00;
    TRISBbits.TRISB0 = 0;
    
    INTCONbits.GIE = 1;     // Tum interruptlara izin verildi
    INTCONbits.PEIE = 1;    // Peripheral interrupt aktif edilerek TMR1 aktif edilir
    
    PIE1bits.TMR1IE = 1;    // TMR1 aktif edildi    PIR1 registerinin TMR1IF si Timer-1'in flag biti
    T1CONbits.TMR1CS = 0;   // TMR1 Zamanalayici olarak ayarlandi
    T1CONbits.T1CKPS0 = 0;  // Bu iki kodda prescaler orani 1:1 
    T1CONbits.T1CKPS1 = 0;  // 1 olarak ayarlandi 
    T1CONbits.TMR1ON = 1;   // TMR1 Enable
    
    TMR1 = 45536;           // TMR1 Baslangic degeri    (10^-6)x(65536-45536)x(1) = 0.02 sn 1 kesme olusma süresi
    
    while(1){
    
    }
    
}
