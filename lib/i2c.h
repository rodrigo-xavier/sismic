#pragma once
#include <msp430.h>
#include <stdint.h>

#define I2C_ADDR 0x50 // I2C address of the slave device


void init_i2c(void)
{
    // Initialize I2C
    P3SEL |= BIT0 + BIT1;                 // Enable I2C pins for USCI_B0
    UCB0CTL1 |= UCSWRST;                  // Software reset enabled
    UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC; // I2C master mode, synchronous mode
    UCB0CTL1 = UCSSEL__SMCLK + UCSWRST;        // SMCLK, software reset enabled
    UCB0BR0 = 12;                         // Clock divider for 100 kHz
    UCB0BR1 = 0;

    // Master
    P3SEL |= BIT0;
    P3REN |= BIT0;
    P3OUT |= BIT0;

    // Slave
    P3SEL |= BIT1;
    P3REN |= BIT1;
    P3OUT |= BIT1;

    UCB0CTL1 &= ~UCSWRST;
}

void i2c_start(void)
{
    UCB0CTL1 |= UCTR + UCTXSTT;
    while (UCB0CTL1 & UCTXSTT);
}

void i2c_stop(void)
{
    UCB0CTL1 |= UCTXSTP;
    while (UCB0CTL1 & UCTXSTP);
}

void i2c_write(uint8_t data)
{
    UCB0TXBUF = data;
    while (!(UCB0IFG & UCTXIFG));
}

void i2c_write_register(uint8_t address, uint8_t data)
{
    i2c_start();
    i2c_write(address);
    i2c_write(data);
    i2c_stop();
}

uint8_t i2c_read(void)
{
    while (!(UCB0IFG & UCRXIFG));
    return UCB0RXBUF;
}

uint8_t i2c_read_register(uint8_t address)
{
    uint8_t data;
    i2c_start();
    i2c_write(address);
    i2c_start();
    UCB0CTL1 &= ~UCTR;
    data = i2c_read();
    i2c_stop();
    return data;
}
