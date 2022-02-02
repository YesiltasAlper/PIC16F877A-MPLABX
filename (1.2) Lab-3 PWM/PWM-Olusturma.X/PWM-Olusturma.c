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

int main() {
    
    TRISB = 0x00;      
    TRISC = 0x00;
    
    PORTB = 0x00;
    PORTC = 0x00;
    
    CCP1CON = 0b00001111;
    T2CON = 0b00000101;     // Prescaler 4
    TMR2 = 0;
    PR2 = 100;
    
    int16_t duty = 200;
    
    CCPR1L = duty>>2;
    CCP1Y = duty&1;
    CCP1X = duty&2;
    
    int16_t deger = (int16_t)(4*CCPR1L + CCP1Y+CCP1X);
    
    lcd_hazirla();
    
    lcd_gotoxy(1,1);
    lcd_yaz("Deger : ");
    veri_yolla((deger%10000)/1000+48);  // binler basamagi
    veri_yolla((deger%1000)/100+48);    // yuzler basamagi
    veri_yolla((deger%100)/10+48);      // onlar basamagi
    veri_yolla((deger%10)+48);          // birler basamagi
        
    while(1);
}



