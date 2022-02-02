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

void __interrupt()compare_kesme(){
    
    if(PIR1bits.CCP1IF)
        PORTBbits.RB0 ^= 1;
    
   PIR1bits.TMR1IF = 0;    // TMR1 Overflow Interrupt Flag bit
   PIR1bits.CCP1IF = 0;    // CCP1 Interrupt Flag Bit
      
}

int main() {
    
    TRISBbits.TRISB0 = 0;
    TRISCbits.TRISC0 = 1;
    TRISCbits.TRISC2 = 0;
    PORTB = 0x00;
    PORTC = 0x00;
  
    INTCONbits.GIE = 1;     // Tum kesmelere izin verildi
    INTCONbits.PEIE = 1;    // TMR1 kesmesini aktif etmek icin
    
    PIE1bits.TMR1IE = 1;    // TMR1 kesmesine izin verildi
    PIE1bits.CCP1IE = 1;    // CCP1'e izin verildi
    
    T1CONbits.T1OSCEN = 1;  // Timer-1 oscillator was enabled
    T1CONbits.T1SYNC = 0;   // Senkronize olarak calisacak sayici modda boyle olmalidir
    T1CONbits.TMR1CS = 1;   // TMR1 sayici olarak 
    T1CONbits.TMR1ON = 1;   // TMR1 aktif
    T1CONbits.T1CKPS0 = 0;  // iki bitten olusan frekans bolucu degeri 
    T1CONbits.T1CKPS1 = 0;  // 1:1 bu sekilde 1
    
    PIR1bits.TMR1IF = 0;    // TMR1 Overflow Interrupt Flag bit
    PIR1bits.CCP1IF = 0;    // CCP1 Interrupt Flag bit
    
    TMR1 = 0;     // TMR1 deger baslangici      
    CCPR1 = 5;    // CCP1 deger baslangici
    
    CCP1CONbits.CCP1M0 = 1; // Bu kodlarin 4 tanesi CCP1'nin modunu ayarlar.Biz boyle yaparak
    CCP1CONbits.CCP1M1 = 1; // TMR1 = CCPR1 oldugunda yani compare kesmesi olusunca
    CCP1CONbits.CCP1M2 = 0; // CCP1 pininin durumu degismesin ne ise oyle kalsin ve kesme olusunca TMR1 = 0 olsun 
    CCP1CONbits.CCP1M3 = 1; // CCP1CONbits.CCP1M = 11; de yazabilabilirdi.
    
    while(1){
    }
}
