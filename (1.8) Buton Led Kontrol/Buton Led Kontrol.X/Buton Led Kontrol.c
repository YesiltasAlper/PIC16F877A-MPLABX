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

int main() {
    
CMCON = 0b00000111;     // compare modu off
ADCON1 = 0b00000111;    // adc modu off

TRISAbits.TRISA0 = 1;   // Giris olarak ayarlandi
TRISBbits.TRISB5 = 0;   // Cikis olarak ayarlandi

if(PORTAbits.RA0 == 1){
    PORTBbits.RB5 = 1;
}
    
else
    PORTBbits.RB5 = 0;

}
