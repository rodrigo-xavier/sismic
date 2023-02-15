#include "../../lib/l298n.h"
#include <msp430.h>


int main(void)
{
    // Parar o watchdog timer
    WDTCTL = WDTPW + WDTHOLD; // Inicializa o PWM

    init_pwm();               // Configura os pinos de controle do L298N como sadas
    P1DIR |= IN1 + IN2;       // Configura o motor para girar no sentido horrio com 50% de velocidade while(1){
    forward();
    __delay_cycles(5000);
    reverse();
    set_pwm_duty_cycle(0.5);
    return 0;
}
