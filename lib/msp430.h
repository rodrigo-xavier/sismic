#include <msp430.h>
#include <stdbool.h>

void GPIO(uint8_t, uint16_t, bool);

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer

  GPIO(2, BIT1, input=true);

  return 0;
}

void GPIO(uint8_t PORT, uint16_t BIT, bool input)
{
  switch (input)
  {
  case true:
    switch (PORT)
    {
    case 1:
      P1DIR |= BIT;  // Configura pino como entrada (zera o bit X de P1DIR)
      P1REN |= BIT;  // Ativa o resistor (habilita o bit X de P1REN)
      P1OUT &= ~BIT; // Seleciona o resistor de pull-down
      break;
    case 2:
      P2DIR |= BIT;
      P2REN |= BIT;
      P2OUT &= ~BIT;
      break;
    case 3:
      P3DIR |= BIT;
      P3REN |= BIT;
      P3OUT &= ~BIT;
      break;
    case 4:
      P4DIR |= BIT;
      P4REN |= BIT;
      P4OUT &= ~BIT;
      break;
    case 5:
      P5DIR |= BIT;
      P5REN |= BIT;
      P5OUT &= ~BIT;
      break;
    case 6:
      P6DIR |= BIT;
      P6REN |= BIT;
      P6OUT &= ~BIT;
      break;
    case 7:
      P7DIR |= BIT;
      P7REN |= BIT;
      P7OUT &= ~BIT;
      break;
    case 8:
      P8DIR |= BIT;
      P8REN |= BIT;
      P8OUT &= ~BIT;
      break;
    default:
      break;
    }
    break;
  case false:
    switch (PORT)
    {
    case 1:
      P1OUT &= ~BIT; // Seleciona o resistor de pull-down
      P1DIR |= BIT;  // Configura pino como entrada (zera o bit X de P1DIR)
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