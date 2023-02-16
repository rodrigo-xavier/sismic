#include "../../lib/l298n.h"
#include "../../lib/mpu6050.h"
#include <msp430.h>


int main(void)
{
    // Parar o watchdog timer
    WDTCTL = WDTPW + WDTHOLD; // Inicializa o PWM

    l298n_init();                       // Configura os pinos de controle do L298N como saidas
    P1DIR |= IN1 | IN2;
    P2DIR |= IN3 | IN4;

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






// volatile int sensorout;

// void main(void)
// {
//     P1DIR |= 0xE7; //defining  P1.4 P1.3  as input, 2 sensors, the rest output
//     P1SEL |= BIT6; //defining P1.6 as timer (PWM)
//     P2DIR = 0xFF;

//     int period = 0x0FFF;  //PWM period

//     float D = 0.52; //duty cycle
//     TACCR0 = period-1;  //PWM period
//     TACCR1 = period*D;  //CCR1 PWM Duty Cycle
//     TACCTL1 = OUTMOD_7;  //CCR1 selection reset-set
//     TACTL = TASSEL_2|MC_1;   //SMCLK submain clock,upmode

//     while (1){
//         sensorout = P1IN & 0x18;// sensor sends high voltage on dark surface
//         if (sensorout == 0x18)
//             straight();
//         else if (sensorout == 0x08)
//             turnright();
//         else if (sensorout ==  0x10)
//             turnleft();
//         else if (sensorout ==  0x00)
//             stop();
//     }
// }
// void straight(void){
//     P2OUT = 0x00;
//     P2OUT |= 0x24;
// }
// void turnright(void){
//     P2OUT = 0x00;
//     P2OUT |= 0x20;
// }
// void turnleft(void){
//     P2OUT = 0x00;
//     P2OUT |= 0x04;
// }
// void stop(void){
//     P2OUT = 0x00;
//     P2OUT |= 0x00;
// }