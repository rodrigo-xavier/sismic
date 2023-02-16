#include "../../lib/l298n.h"
#include "../../lib/mpu6050.h"
#include <msp430.h>


// int main(void)
// {
//     WDTCTL = WDTPW + WDTHOLD; // Inicializa o PWM

//     l298n_init(); // Configura o módulo L298N

//     forward();
//     // __delay_cycles(5000);
//     // reverse();
//     l298n_config_pwm(0.6);
//     return 0;
// }


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    i2c_init();
    mpu6050_init();

    // Enable global interrupts
    _BIS_SR(GIE);

    while (1)
    {
        mpu6050_read();
        filter_data();
    }
}



#include <msp430.h>
#include <stdint.h>
/**
* main.c
*/

void i2cConfigMaster();
void i2cConfigeSlave();
uint8_t i2cSend(uint8_t addr, uint8_t data);

int main(void)
{
   WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
   i2cConfigMaster();
   i2cConfigeSlave(); 
   __enable_interrupt(); 
   i2cSend(0x34, 8); 
   while(1); 
   return 0;
}

uint8_t i2cSend(uint8_t addr, uint8_t data) {
   UCB0I2CSA = addr; UCB0CTL1 |= UCTR | UCTXSTT;
   UCB0TXBUF = data; while(UCB0CTL1 & UCTXSTT); UCB0CTL1 |= UCTXSTP; while(UCB0CTL1 & UCTXSTP); if(UCB0IFG & UCNACKIFG) {
      return 1;
   }
   else{
      return 0;
   }
}

void i2cConfigMaster() {
   UCB0CTL1 = UCSWRST;
   UCB0CTL0 = UCMST | UCMODE_3 | UCSYNC;
   UCB0CTL1 |= UCSSEL__SMCLK;
   UCB0BRW = 10; P3SEL |= BIT0 | BIT1;
   P3REN |= BIT0 | BIT1;
   P3OUT |= BIT0 | BIT1;
   UCB0CTL1 &= ~UCSWRST;
}
   
void i2cConfigeSlave() {
   UCB1CTL1 = UCSWRST;
   UCB1CTL0 = UCMODE_3 | UCSYNC;
   UCB1I2COA = 0x34;
   P4SEL |= BIT1 | BIT2;
   P4REN |= BIT1 | BIT2;
   P4OUT |= BIT1 | BIT2;
   UCB1CTL1 &= ~UCSWRST;
   UCB1IE |= UCTXIE | UCRXIE;
}

#pragma vector = USCI_B1_VECTOR
__interrupt void b1_rec(void){
   switch(UCB0IV){
      case USCI_I2C_UCRXIFG:
         break; case USCI_I2C_UCTXIFG: break;
   }
}