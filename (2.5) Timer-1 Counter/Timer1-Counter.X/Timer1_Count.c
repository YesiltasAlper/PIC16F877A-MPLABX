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

void __interrupt()timer1_counter(){
    TMR1 = 65535;
    static unsigned int counter = 0;
    counter++;
    
    if(PIR1bits.TMR1IF && counter < 16){
        PORTB = counter;
    }
    
    if(PIR1bits.TMR1IF && counter > 15){
        counter = 0;
    }
    
    PIR1bits.TMR1IF = 0;
}

int main() {
    
    PORTB = 0x00;           // PORTB clear edildi
    TRISBbits.TRISB0 = 0;   // Giris cikis ayarlamalari
    TRISBbits.TRISB1 = 0;   // Giris cikis ayarlamalari
    TRISBbits.TRISB2 = 0;   // Giris cikis ayarlamalari
    TRISBbits.TRISB3 = 0;   // Giris cikis ayarlamalari
    
    INTCONbits.GIE = 1;     // Tum kesmelere izin verildi
    INTCONbits.PEIE = 1;    // TMR1 kesmesini aktif etmek icin PEIE = 1 edildi
    
    PIE1bits.TMR1IE = 1;    // TMR1 kesmesine izin verildi
    
    T1CONbits.TMR1CS = 1;   // TMR1 sayici olarak 
    T1CONbits.TMR1ON = 1;   // TMR1 aktif
    T1CONbits.T1CKPS0 = 0;  // iki bitten olusan frekans bolucu degeri 
    T1CONbits.T1CKPS1 = 0;  // bu sekilde 1:1 yani 1
    
    TMR1 = 65535;           // TMR1 bu degerden saymaya baslasin
    
    while(1){
    }
}
