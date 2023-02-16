#include "../../lib/l298n.h"
#include "../../lib/mpu6050.h"
#include <msp430.h>


int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Inicializa o PWM

    l298n_init(); // Configura o módulo L298N

    forward();
    // __delay_cycles(5000);
    // reverse();
    l298n_config_pwm(0.6);
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
