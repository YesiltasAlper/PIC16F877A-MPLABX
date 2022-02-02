#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF         // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

unsigned char sayici;
unsigned char adres = 0x00;

int main() {
    TRISB = 0x00;
    TRISD = 0x01;
    PORTB = 0x00;
    PORTD = 0x00;
   
    sayici = eeprom_read(adres);    // 0x00 belle?indeki veriyi sayici de?i?kenine aktard?k (Say?c? art?k eeprom'da diye söylüyor)
    while(1){
        if(RD0){
            while(RD0);
            ++sayici;
            eeprom_write(adres,sayici);     // 0x00 adresine say?c? de?eri yaz?l?r.Yani sayiciyi artt?r?yosun ama o adreste oldugunu söyle
            if(sayici == 4){
                sayici = 0;
            }   
            PORTB = eeprom_read(adres);     // 0x00 belle?indeki veriyi PORTB'ye aktard?k.Bunu yapmasak PORTB'ye yazd?rmaz.
        }
    }
}
