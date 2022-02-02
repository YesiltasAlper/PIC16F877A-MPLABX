#include"portb_interrupt_config.h"
#include<xc.h>

void ei_portb(void){        // enable PortB change interrupt (RB4-RB5-RB6-RB7)
    INTCONbits.GIE = 1;     // enable all interrupts
    INTCONbits.RBIE = 1;    // enable PORTB change interrupt
                            // INTCONbits.RBIF PORTB'nin flag biti.
}
