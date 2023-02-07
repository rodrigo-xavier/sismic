#include <stdint.h>
#include <stdbool.h>
#include <msp430.h>
#include "../../lib/xavier.h"


void exercise2_1(void);
void exercise2_2(void);


void main(void)
{
    exercise2_2();
}


void exercise2_1(void){
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    GPIO(2, BIT1, true);        // Configura o pino do botão S1 como entrada
    GPIO(4, BIT7, false);       // Configura o pino do led verde como saída

    while(1){
        if (!(P2IN & BIT1))
            P4OUT |= BIT7;
        else
            P4OUT &= ~BIT7;
    }
}

void exercise2_2(void){
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    GPIO(2, BIT1, true);
    GPIO(1, BIT0, false);

    while(1){
        if (!(P2IN & BIT1))
            P4OUT |= BIT7;
        else
            P4OUT &= ~BIT7;
    }
}
