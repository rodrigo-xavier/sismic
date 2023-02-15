#include <msp430.h>

// Define os pinos de controle do L298N
#define ENA BIT2 // P1.2
#define IN1 BIT3 //
#define IN2 BIT4

// Define a frequncia do PWM
#define PWM_FREQ 1000


void init_pwm() {
 // Configura o pino ENA como sada PWM
 P1DIR |= ENA;
 P1SEL |= ENA; // Configura o timer TA0 como fonte de clock para o PWM
 TA0CTL = TASSEL_2 + MC_1;
 TA0CCR0 = (unsigned int) ((float) (1000000 / PWM_FREQ));
 TA0CCTL1 = OUTMOD_7;
}

void set_pwm_duty_cycle(float duty_cycle) {
 // Configura o ciclo de trabalho do PWM
 TA0CCR1 = (unsigned int) ((float) (duty_cycle * TA0CCR0));
}

void forward() {
 // Configura o L298N para girar o motor no sentido horrio
 P1OUT |= IN1;
 P1OUT &= ~IN2;
}

void reverse() {
 // Configura o L298N para girar o motor no sentido anti-horrio
 P1OUT &= ~IN1;
 P1OUT |= IN2;
}

void stop() {
 // Configura o L298N para parar o motor
 P1OUT &= ~IN1;
 P1OUT &= ~IN2;
}

int main(void) {
 // Parar o watchdog timer
 WDTCTL = WDTPW + WDTHOLD; // Inicializa o PWM
 init_pwm(); // Configura os pinos de controle do L298N como sadas
 P1DIR |= IN1 + IN2; // Configura o motor para girar no sentido horrio com 50% de velocidade while(1){
 forward();
 __delay_cycles(5000);
 reverse();
 set_pwm_duty_cycle(0.5);
 } //__bis_SR_register(LPM0_bits + GIE);
 return 0;
}
