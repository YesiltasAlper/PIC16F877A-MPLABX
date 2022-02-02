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

void __interrupt()timer2(){
    
    TMR2 = 0;
    PR2 = 200;
    
    if(PIE1bits.TMR2IE && PIR1bits.TMR2IF){
        
        const unsigned int seven_segment[] = {63,6,91,79,102,109,124,7,127,111};
        static unsigned int counter = 0;
        static unsigned int i = 0;
        
        counter++;
        
        if(counter == 500){
            PORTB = seven_segment[i];
            i++;
            counter = 0;
        }
        
        if(i == 10)
            i = 0; 
    }
    
    PIR1bits.TMR2IF = 0;    // flag = 0
}

int main() {
    PORTB = 0x00;   // PortB Clear edildi
    TRISB = 0x00;   // B portunun hepsi cikis olarak ayarlandi
    
    INTCONbits.GIE = 1;     // tum interruptlara izin
    INTCONbits.PEIE = 1;	// TMR2'ye izin verilmesi icin acmamiz gerek cunku TMR1 ve TMR2 Peripheral'da bulunur
    
    PIR1bits.TMR2IF = 0;    // TMR2 to PR2 Match Interrupt Flag bit clear edildi
    
    PIE1bits.TMR2IE = 1;    // TMR2 kesmesine izin verildi
    
    T2CONbits.TOUTPS0 = 1;  // Bu bitler postscale ayarlama bitleri
    T2CONbits.TOUTPS1 = 0;  // Postscale degeri 1:10 olarak ayarlandi
    T2CONbits.TOUTPS2 = 0;  // TMR2 degeri PR2 degerine
    T2CONbits.TOUTPS3 = 1;  // 10 kez esit olunca kesme olusacak
    
    T2CONbits.TMR2ON = 1;   // TMR2 aktif
    
    T2CONbits.T2CKPS0 = 0;  // Timer2 bolme orani ayarlama bitleri
    T2CONbits.T2CKPS1 = 0;  // burada bolme orani 1:1 ayarlandi
    
    TMR2 = 0;   // TMR2 0'dan baslasin
    PR2 = 200;  // 200 e kadar saysin
    
    while(1){
    }
    
}
