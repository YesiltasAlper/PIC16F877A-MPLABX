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

void __interrupt()timer_counter(){
    
    static unsigned int counter = 0;    // Otomatik omurlu olursa fonksiyon buradan ciktigi zaman counter 0 olur.  
    
    TMR0 = 253;     // 256 dan sonra tasma oluyor ve bu deger 0 oldugu icin bu degeri tekrar hatirlatiyoruz
     ++counter;
    
    if(INTCONbits.TMR0IF && counter == 1){
        PORTBbits.RB0 = 1;
        PORTBbits.RB1 = 0;
    }
    
    if(INTCONbits.TMR0IF && counter == 2){
        PORTBbits.RB0 = 0;
        PORTBbits.RB1 = 1;
        counter = 0;
    }
    
    INTCONbits.TMR0IF = 0;  // TMR0IF   flag bit eger bunu her cikista sifirlamazsak 1 olur ve surekli kesme var gibi algilar.
}

int main() {
    
    PORTB = 0;
    TRISAbits.TRISA4 = 1;
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    
    INTCONbits.GIE = 1;         // Tum interruptlara izin verildi
    INTCONbits.TMR0IE = 1;      // TMR0 aktif edildi
    OPTION_REGbits.T0CS = 1;    // TMR0 sayici olarak ayarlandi
    OPTION_REGbits.T0SE = 1;    // Yukselen kenarda sinyal okunacak
    OPTION_REGbits.PSA = 0;     // Bolme orani TMR0 icin kullanilacak
    
    OPTION_REGbits.PS0 = 0;     // Burada 1:2 frekans bolme orani secildi.
    OPTION_REGbits.PS1 = 0;
    OPTION_REGbits.PS2 = 0;
    
    TMR0 = 253;                 // TMR0 degeri 253 den baslayacak.  (256-253)x(2) = 6 
                                // (256 - TMR0 degeri) x (Frekans bolucu orani)
    while(1){
    }
    
}
