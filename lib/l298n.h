#pragma once
#include <msp430.h>

// Define a frequncia do PWM
#define PWM_FREQ 1000

// Define os pinos de controle do L298N
#define ENA BIT2 // P1.2
#define IN1 BIT3 // P1.3
#define IN2 BIT4 // P1.4

#define ENB BIT0 // P2.0
#define IN3 BIT2 // P2.2
#define IN4 BIT4 // P2.4


void init_l298n_pwm(void);
void set_l298n_pwm_duty_cycle(float duty_cycle);
void foward(void);
void reverse(void);
void stop(void);


void init_l298n_pwm(void)
{
    // Configura o pino ENA como saida PWM
    P1DIR |= ENA;
    P1SEL |= ENA;
    P2DIR |= ENB;
    P2SEL |= ENB;

    TA0CTL = TASSEL__SMCLK + MC__UP;
    TA0CCR0 = (unsigned int)(1000000 / PWM_FREQ);
    TA0CCTL1 = OUTMOD_7;
    TA0CCTL2 = OUTMOD_7;
}

void set_l298n_pwm_duty_cycle(float duty_cycle)
{
    TA0CCR1 = (unsigned int)(duty_cycle * TA0CCR0);
    TA0CCR2 = (unsigned int)(duty_cycle * TA0CCR0);
}

void forward(void)
// Configura o L298N para girar o motor no sentido horario
{
    P1OUT |= IN1;
    P1OUT &= ~IN2;

    P2OUT |= IN3;
    P2OUT &= ~IN4;

    P2OUT |= ENB; // Liga o pino ENB para acionar o motor
}

void reverse(void)
// Configura o L298N para girar o motor no sentido anti-horario
{
    P1OUT &= ~IN1;
    P1OUT |= IN2;

    P2OUT &= ~IN3;
    P2OUT |= IN4;

    P2OUT |= ENB; // Liga o pino ENB para acionar o motor
}

void stop(void)
// Configura o L298N para parar o motor
{
    P1OUT &= ~IN1;
    P1OUT &= ~IN2;

    P2OUT &= ~IN3;
    P2OUT &= ~IN4;

    P2OUT &= ~ENB; // Desliga o pino ENB para parar o motor
}
