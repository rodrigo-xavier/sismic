#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <msp430.h>


void GPIO(uint8_t, uint16_t, bool);
void debounce_counter(void);


void GPIO(uint8_t PORT, uint16_t BIT, bool ENABLE)
{
  switch (ENABLE)
  {
  case true:
    switch (PORT)
    {
    case 1:
      P1DIR &= ~BIT;  // Configura pino como entrada (zera o bit X de P1DIR)
      P1OUT |= BIT;   // Seleciona o resistor de pull-up
      P1REN |= BIT;   // Ativa o resistor (habilita o bit X de P1REN)
      break;
    case 2:
      P2DIR &= ~BIT;
      P2OUT |= BIT;
      P2REN |= BIT;
      break;
    case 3:
      P3DIR &= ~BIT;
      P3OUT |= BIT;
      P3REN |= BIT;
      break;
    case 4:
      P4DIR &= ~BIT;
      P4OUT |= BIT;
      P4REN |= BIT;
      break;
    case 5:
      P5DIR &= ~BIT;
      P5OUT |= BIT;
      P5REN |= BIT;
      break;
    case 6:
      P6DIR &= ~BIT;
      P6OUT |= BIT;
      P6REN |= BIT;
      break;
    case 7:
      P7DIR &= ~BIT;
      P7OUT |= BIT;
      P7REN |= BIT;
      break;
    case 8:
      P8DIR &= ~BIT;
      P8OUT |= BIT;
      P8REN |= BIT;
      break;
    default:
      break;
    }
    break;
  case false:
    switch (PORT)
    {
    case 1:
    // OUT vem antes do DIR por uma boa prática de programação, com a finalidade de evitar glitches
      P1OUT &= ~BIT; // Limpa a saída
      P1DIR |= BIT;  // Configura pino como saída (seta em 1 o bit X de P1DIR)
      break;
    case 2:
      P2OUT &= ~BIT;
      P2DIR |= BIT;
      break;
    case 3:
      P3OUT &= ~BIT;
      P3DIR |= BIT;
      break;
    case 4:
      P4OUT &= ~BIT;
      P4DIR |= BIT;
      break;
    case 5:
      P5OUT &= ~BIT;
      P5DIR |= BIT;
      break;
    case 6:
      P6OUT &= ~BIT;
      P6DIR |= BIT;
      break;
    case 7:
      P7OUT &= ~BIT;
      P7DIR |= BIT;
      break;
    case 8:
      P8OUT &= ~BIT;
      P8DIR |= BIT;
      break;
    default:
      break;
    }
  }
}


void debounce_counter(){
  volatile int i = 50000;
  while(i--);
}