#include"interrupt_config.h"
#include<xc.h>

void ei_ex_rising(void){
    INTCONbits.GIE = 1;             // Tum kesmelere izin verildi    // INTF external flag bit,kesme olusursa 1 normalde 0
    INTCONbits.INTE = 1;            // RB0 kesmesi aktif edildi
    OPTION_REGbits.INTEDG = 1;      // Yukselen-Dusen kenar seciminden yukselen kenar secildi
}

void ei_ex_falling(void){
    INTCONbits.GIE = 1;             // Tum kesmelere izin verildi    // INTF external flag bit,kesme olusursa 1 normalde 0
    INTCONbits.INTE = 1;            // RB0 kesmesi aktif edildi
    OPTION_REGbits.INTEDG = 0;      // Yukselen-Dusen kenar seciminden dusen kenar secildi
}


