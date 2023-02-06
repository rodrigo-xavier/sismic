#include <msp430.h>
#include "../../lib/xavier.h"


void exercise2_1(void);


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    exercise2_1();

}


void exercise2_1(void){
    GPIO(2, BIT1, true);    // Configure port P2.1 as input

    while(1){
        P1OUT ^= BIT0;
        __delay_cycles(1000000);
    }
}
