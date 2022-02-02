#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#include<stdint.h>
#include "lcd_library.h"

#define     _XTAL_FREQ       4000000

int16_t duty = 0;
const float oran = 400.0/1023.0;

int main() {
    
    TRISA = 0x01;
    TRISB = 0x00;      
    TRISC = 0x00;
    
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    
    ADCON0bits.ADON = 1;    // A/D converter module is powered up
    ADCON0bits.GO_DONE = 0; // A/D conversion is not in progress yet 
    ADCON0bits.CHS0 = 0;    // AN0 RA0 pini analog
    ADCON0bits.CHS1 = 0;    // kanal olarak
    ADCON0bits.CHS2 = 0;    // secildi
    ADCON0bits.ADCS0 = 0;   // Fosc/2
    ADCON0bits.ADCS1 = 0;   // secildi
    
    ADCON1bits.PCFG0 = 0;   // A portunun RA0 pini analog 
    ADCON1bits.PCFG1 = 1;   // diger pinler digital secildi
    ADCON1bits.PCFG2 = 1;   // Vref+ = +5V  Vref- = Vss
    ADCON1bits.PCFG3 = 1;   // secildi.
    ADCON1bits.ADCS2 = 0;   // Fosc/2 secildigi icin 0 olmali.
    
    ADCON1bits.ADFM = 1;    // 10 bit okuma yapmak icin 1 yapildi
    // 8 bitlik 2 ayri register olan ADRESH ve ADRESL registerlari
    // ADRESH saga dayali secildi bu sebeple ADRESH'nin ilk 2 biti
    // 256 ve 512 olarak okunarak 10 bit ayarlama yapildi.
    
    CCP2CON = 0b00001111;   // CCP2 Modulu PWM ayarlandi CCP1 digital kaldi
    T2CON = 0b00000101;     // T2 ON,Prescale 4
    
    TMR2 = 0;
    PR2 = 99;

    lcd_hazirla();
    
    while(1){
    
        ADCON0bits.GO_DONE = 1;         // A/D conversion is in progress 
        while(ADCON0bits.GO_DONE){};    // ADC'nin ayarlanmasi icin beklendi
        
        PORTCbits.RC2 = 1;              // Motor ileri
        PORTCbits.RC3 = 0;              // yonde calisir
            
        duty = (int16_t)((ADRESH*256+ADRESL)*oran);
        
        CCPR2L = duty>>2;
        CCP2Y = duty&1;
        CCP2X = duty&2;
        
        lcd_gotoxy(1,1);
        lcd_yaz("Analog ");
        veri_yolla(((ADRESH*256+ADRESL)%10000)/1000+48);
        veri_yolla(((ADRESH*256+ADRESL)%1000)/100+48);
        veri_yolla(((ADRESH*256+ADRESL)%100)/10+48);
        veri_yolla(((ADRESH*256+ADRESL)%10)+48);
        
        lcd_gotoxy(2,1);
        lcd_yaz("Duty ");
        veri_yolla(((duty)%10000)/1000+48);
        veri_yolla(((duty)%1000)/100+48);
        veri_yolla(((duty)%100)/10+48);
        veri_yolla(((duty)%10)+48);
    }
}



