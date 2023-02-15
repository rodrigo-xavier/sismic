#include <msp430.h>
#include <stdint.h>

#define MPU6050_ADDRESS 0x68

// Complementary filter constant
#define ALPHA 0.98

// Flags to indicate when a read or write is complete
volatile uint8_t i2c_write_done = 0;
volatile uint8_t i2c_read_done = 0;

// Function prototypes
void i2c_init(void);
void i2c_write(uint8_t reg, uint8_t data);
uint8_t i2c_read(uint8_t reg);



void i2c_init(void)
{
    // Configure I2C peripheral
    UCB0CTL1 |= UCSWRST;        // Put state machine in reset
    UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;  // I2CMaster, synchronous mode
    UCB0CTL1 = UCSSEL_2 + UCSWRST;  // Use SMCLK, keep in reset
    UCB0BR0 = 12;             // fSCL = SMCLK/12 = ~100kHz
    UCB0BR1 = 0;
    UCB0CTL1 &= ~UCSWRST;       // Release state machine

    UCB0I2CSA = MPU6050_ADDRESS;  // Set slave address

    UCB0IE |= UCNACKIE + UCSTTIE + UCSTPIE + UCALIE;   // Enable I2C interrupts
}

void i2c_write(uint8_t reg, uint8_t data)
{
    i2c_write_done = 0;
    UCB0CTL1 |= UCTR + UCTXSTT;    // I2C TX, start condition
    UCB0TXBUF = reg;              // Send register address
    while (!i2c_write_done);
    UCB0TXBUF = data;             // Send data
    while (!i2c_write_done);
}

uint8_t i2c_read(uint8_t reg)
{
    uint8_t data;
    i2c_read_done = 0;
    UCB0CTL1 |= UCTR + UCTXSTT;    // I2C TX, start condition
    UCB0TXBUF = reg;              // Send register address
    while (!i2c_read_done);
    UCB0CTL1 &= ~UCTR;            // I2C RX, change direction
    UCB0CTL1 |= UCTXSTT;          // I2C start condition
    while (!i2c_read_done);
    data = UCB0RXBUF;              // Read data
    return data;
}

