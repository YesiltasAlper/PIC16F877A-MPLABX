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

typedef union{
    
    struct{
        unsigned int RB0 : 1;
        unsigned int RB1 : 1;
        unsigned int RB2 : 1;
        unsigned int RB3 : 1;
        unsigned int RB4 : 1;
        unsigned int RB5 : 1;
        unsigned int RB6 : 1;
        unsigned int RB7 : 1;
    };
}portb_pins_portb;

typedef union{
    
    struct{
        unsigned int RB0 : 1;
        unsigned int RB1 : 1;
        unsigned int RB2 : 1;
        unsigned int RB3 : 1;
        unsigned int RB4 : 1;
        unsigned int RB5 : 1;
        unsigned int RB6 : 1;
        unsigned int RB7 : 1;
    };
}portb_pins_trisb;

int main() {
    
    while(1){
    
        portb_pins_trisb * const TRIS_B_pin = (portb_pins_trisb *)0x86;

        TRIS_B_pin ->RB0 = 0;   // Cikis olarak ayarlandilar
        TRIS_B_pin ->RB3 = 0;
        TRIS_B_pin ->RB7 = 0;


        volatile portb_pins_portb * const PORT_B_pin = (portb_pins_portb *)0x06;

        PORT_B_pin ->RB0 = 0;   // Kaydediciler sifirlandi lojik-0 verildi "0V"
        PORT_B_pin ->RB1 = 0;
        PORT_B_pin ->RB2 = 0;
        PORT_B_pin ->RB3 = 0;
        PORT_B_pin ->RB4 = 0;
        PORT_B_pin ->RB5 = 0;
        PORT_B_pin ->RB6 = 0;
        PORT_B_pin ->RB7 = 0;
        
        __delay_ms(500);        // Gecikme
        
        PORT_B_pin ->RB0 = 1;   // Portlara lojik-1 verildi "+5V"
        PORT_B_pin ->RB3 = 1;
        PORT_B_pin ->RB7 = 1;

        __delay_ms(1000);       // Gecikme

    }
    
}

