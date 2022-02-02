# 1 "Eeprom-Kesmesi.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v5.45/packs/Microchip/PIC16Fxxx_DFP/1.2.33/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "Eeprom-Kesmesi.c" 2
#pragma config BOREN = OFF
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

unsigned char sayici;
unsigned char adres = 0x00;

int main() {
    TRISB = 0x00;
    TRISD = 0x01;
    PORTB = 0x00;
    PORTD = 0x00;

    sayici = eeprom_read(adres);
    while(1){
        if(RD0){
            while(RD0);
            ++sayici;
            eeprom_write(adres,sayici);
            if(sayici == 4){
                sayici = 0;
            }
            PORTB = eeprom_read(adres);
        }
    }
}
