#pragma once
#include <msp430.h>

// Define a frequncia do PWM
#define PWM_FREQ 1000

// Define os pinos de controle do L298N
#define ENA BIT2 // P1.2
#define IN1 BIT3 // P1.3
#define IN2 BIT4 // P1.4

#define ENB BIT0 // P1.2
#define IN3 BIT2 // P1.3
#define IN4 BIT4 // P1.4


void l298n_init(void);
void l298n_config_pwm(float duty_cycle);
void foward(void);
void reverse(void);
void stop(void);


void l298n_init(void)
{
    // Configura o pino ENA e ENB como saida PWM
    P1DIR |= ENA | ENB;
    P1SEL |= ENA | ENB;

    TA0CTL = TASSEL__SMCLK | MC__UP;
    TA0CCR0 = (unsigned int)((float)(1000000 / PWM_FREQ));
    TA0CCTL1 = OUTMOD_7;
}

void l298n_config_pwm(float duty_cycle)
{
    // Configura o PWM, o duty_cycle pode servier como controle de velocidade
    TA0CCR1 = (unsigned int)((float)(duty_cycle * TA0CCR0));
}

void forward(void)
{
    // Configura o L298N para girar o motor no sentido horario

    /*  All below in once line:
    P1OUT |= IN1;
    P1OUT &= ~IN2;
    P2OUT |= IN3;
    P2OUT &= ~IN4;
    */

    P1OUT = (((P1OUT | IN1) & ~IN2) | IN3) & ~IN4;
}

void reverse(void)
{
    // Configura o L298N para girar o motor no sentido anti-horario
    P1OUT = (((P1OUT & ~IN1) | IN2) & ~IN3) | IN4;
}

void stop(void)
{
    // Configura o L298N para parar o motor
    P1OUT = (((P1OUT & ~IN1) & ~IN2) & ~IN3) & ~IN4;
}
