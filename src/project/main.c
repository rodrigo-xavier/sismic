#include "../../lib/l298n.h"
#include <msp430.h>


int main(void)
{
    // Parar o watchdog timer
    WDTCTL = WDTPW + WDTHOLD; // Inicializa o PWM

    init_l298n_pwm();               // Configura os pinos de controle do L298N como sadas
    P1DIR |= IN1 + IN2;       // Configura o motor para girar no sentido horrio com 50% de velocidade while(1){
    forward();
    __delay_cycles(5000);
    reverse();
    set_l298n_pwm_duty_cycle(0.5);
    return 0;
}


// void mpu6050main(void)
// {
//     WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

//     i2c_init();
//     mpu6050_init();

//     // Enable global interrupts
//     _BIS_SR(GIE);

//     while (1)
//     {
//         mpu6050_read();
//         filter_data();
//     }
// }