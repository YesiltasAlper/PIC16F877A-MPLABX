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

int display_onlar[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7C,0x07,0x7F,0x6F};
int display_birler[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7C,0x07,0x7F,0x6F};

int main() {
    
    PORTB = 0;
    PORTC = 0;
    
    TRISB = 0x00;
    TRISC = 0x00;
    
    
    while(1){

        for(int i = 0; i < 10; i++){

            PORTC = display_onlar[i];
            __delay_ms(50);
            
            for(int j = 0; j < 10; j++){

                PORTB = display_birler[j];
                __delay_ms(50);
            }
        }
    }
    
    
    // IKINCI YOL
    
    /*
    int onlar = 0;
    int birler = 0;
    
    while(1){
        
        for(int i = 0; i < 100; i++){
            onlar = i /10;
            birler = i%10;

            PORTB = display_birler[birler];
            __delay_ms(50);
            PORTC = display_onlar[onlar];
            __delay_ms(50);
        }
    }
    */
     
}
