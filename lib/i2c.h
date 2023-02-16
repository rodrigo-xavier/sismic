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
    UCB0CTL1 = UCSSEL_2 + UCSWRST;        // SMCLK, software reset enabled
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

    UCB0CTL1 &= ~UCSWRST; // Release software reset
}

void i2c_start(void)
{
    UCB0CTL1 |= UCTR + UCTXSTT; // Transmit mode, start condition
    while (UCB0CTL1 & UCTXSTT); // Wait for start condition to complete
}

void i2c_stop(void)
{
    UCB0CTL1 |= UCTXSTP; // Stop condition
    while (UCB0CTL1 & UCTXSTP); // Wait for stop condition to complete
}

void i2c_write(uint8_t data)
{
    UCB0TXBUF = data; // Write data to TX buffer
    while (!(UCB0IFG & UCTXIFG)); // Wait for TX buffer to be empty
}

void i2c_write_register(uint8_t address, uint8_t data)
{
    i2c_start();        // Start condition
    i2c_write(address); // Write address
    i2c_write(data);    // Write data
    i2c_stop();         // Stop condition
}

uint8_t i2c_read(void)
{
    while (!(UCB0IFG & UCRXIFG));             // Wait for data to be received
    return UCB0RXBUF; // Read data from RX buffer
}

uint8_t i2c_read_register(uint8_t address)
{
    uint8_t data;
    i2c_start();        // Start condition
    i2c_write(address); // Write address
    i2c_start();        // Repeated start condition
    UCB0CTL1 &= ~UCTR;  // Receive mode
    data = i2c_read();  // Read data
    i2c_stop();         // Stop condition
    return data;
}
