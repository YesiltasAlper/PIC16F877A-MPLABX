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

void __interrupt()timer0inter(){
    
    TMR0 = 59;                          // TMR0 degeri 255 olunca sifirlanir ve saniyenin hep 0.050176 olmasi icin her giriste 59 degeri ile baslamali
    
    static unsigned int i = 0;          // Global olarak tanimlamiyorsak static yazilmalidir.Eger otomatik omurlu olursa 
                                        // program kesmeden cikinca degeri sifirlanir.
    if(INTCONbits.TMR0IF && i == 20){   // Eger flag biti 1 ise kesme olusmustur.  i == 20 ise saniye == 1 olmustur
        PORTBbits.RB0 = 1;
    }
    
    if(INTCONbits.TMR0IF && i == 40){   // Eger kesme olusmussa ve i == 40 saniye == 2 olduysa
        PORTBbits.RB0 = 0;
        i = 0;                          
    }
    
    i++;                                
    INTCONbits.TMR0IF = 0;              // Kesmenin bittigini biz bildirmeliyiz. flag = 0; ise kesme bitmistir   
}

int main() {
    
    INTCONbits.GIE = 1;         // Tum intterruptlar aktif
    INTCONbits.TMR0IE = 1;      // TMR0 aktif
    OPTION_REGbits.T0CS = 0;    // TMR0 Zamanlayici olarak ayarlandi
    OPTION_REGbits.PSA = 0;     // Bolme orani TMR0 icin kullanilacak
    OPTION_REG = 7;             // PSA0 : 1  PSA1 : 1  PSA2 : 1;    1/256 Frekans bolucu orani bolme orani secildi.
    TMR0 = 59;                  // TMR0 Degeri 59 dan baslayacak
    
                                // Kesme olusma suresi : Tkomut x (Frekans bolucu orani) x (255 - TMR0 baslangic degeri);
                                // Fkomut = Fosc/4  Tkomut = 1/Fkomut = 1Mhz    Frekans bolucu orani : 256 TMR0 = 59 sure : 0.050176 sn olur
    
    TRISBbits.TRISB0 = 0;       // PORTB RB0 cikis olarak ayarlandi
    PORTB = 0x00;               // PORTB sifirlandi
    
    while(1);
}
