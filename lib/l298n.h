#pragma once
#include <msp430.h>

// Define os pinos de controle do L298N
#define ENA BIT2 // P1.2
#define IN1 BIT3 // P1.3
#define IN2 BIT4 // P1.4

// Define a frequncia do PWM
#define PWM_FREQ 1000


void init_l298_pwm(void);
void set_l298n_pwm_duty_cycle(float duty_cycle);
void foward(void);
void reverse(void);
void stop(void);


void init_l298_pwm()
{
    // Configura o pino ENA como saida PWM
    P1DIR |= ENA;
    P1SEL |= ENA;

    TA0CTL = TASSEL__SMCLK + MC__UP;
    TA0CCR0 = (unsigned int)((float)(1000000 / PWM_FREQ));
    TA0CCTL1 = OUTMOD_7;
}

void set_l298n_pwm_duty_cycle(float duty_cycle)
{
    TA0CCR1 = (unsigned int)((float)(duty_cycle * TA0CCR0));
}

void forward()
// Configura o L298N para girar o motor no sentido horario
{
    P1OUT |= IN1;
    P1OUT &= ~IN2;
}

void reverse()
// Configura o L298N para girar o motor no sentido anti-horario
{
    P1OUT &= ~IN1;
    P1OUT |= IN2;
}

void stop()
// Configura o L298N para parar o motor
{
    P1OUT &= ~IN1;
    P1OUT &= ~IN2;
}
