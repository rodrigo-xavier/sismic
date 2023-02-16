#include <msp430.h>
#include <stdint.h>

#define MPU6050_ADDRESS 0x68

// MPU6050 Register addresses
#define MPU6050_ACCEL_XOUT_H 0x3B
#define MPU6050_GYRO_XOUT_H 0x43

// Complementary filter constant
#define ALPHA 0.98

// Global variables
float filtered_angle = 0;
float raw_angle = 0;
float raw_rate = 0;

// Flags to indicate when a read or write is complete
volatile uint8_t i2c_write_done = 0;
volatile uint8_t i2c_read_done = 0;

// Function prototypes
void i2c_init(void);
void i2c_write(uint8_t reg, uint8_t data);
uint8_t i2c_read(uint8_t reg);
void mpu6050_init(void);
void mpu6050_read(void);
void filter_data(void);


void i2c_init(void)
{
    // Configure I2C peripheral
    UCB0CTL1 |= UCSWRST;        // Put state machine in reset
    UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;  // I2CMaster, synchronous mode
    UCB0CTL1 = UCSSEL_SMCLK + UCSWRST;  // Use SMCLK, keep in reset
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

void mpu6050_init(void)
{
    // Wake up the MPU6050
    i2c_write(0x6B, 0x00);  // PWR_MGMT_1 register, set to zero to wake the MPU6050 up
}

void mpu6050_read(void)
{
    uint8_t high, low;
    // Read the raw accelerometer data
    high = i2c_read(MPU6050_ACCEL_XOUT_H);
    low = i2c_read(MPU6050_ACCEL_XOUT_H + 1);
    raw_angle = (high << 8) | low;
    // Read the raw gyroscope data
    high = i2c_read(MPU6050_GYRO_XOUT_H);
    low = i2c_read(MPU6050_GYRO_XOUT_H + 1);
    raw_rate = (high << 8) | low;
}

void filter_data(void)
{
    // Apply complementary filter
    filtered_angle = ALPHA * (filtered_angle + raw_rate) + (1 - ALPHA) * raw_angle;
}


// Interrupt service routine for I2C
#pragma vector = USCI_B0_VECTOR
__interrupt void USCI_B0_ISR(void)
{
    switch(UCB0IV)
    {
        case USCI_I2C_UCNACKIFG:
            UCB0CTL1 |= UCTXSTP;           // I2C stop condition
            UCB0IFG &= ~UCNACKIFG;         // Clear NACK flag
            break;
        case USCI_I2C_UCSTTIFG:
            UCB0IFG &= ~UCSTTIFG;          // Clear start condition flag
            break;
        case USCI_I2C_UCSTPIFG:
            UCB0IFG &= ~UCSTPIFG;          // Clear stop condition flag
            if (UCB0CTL1 & UCTR) {         // If in transmit mode
                i2c_write_done = 1;
            } else {                      // If in receive mode
                i2c_read_done = 1;
            }
            break;
        case USCI_I2C_UCALIFG:
            UCB0IFG &= ~UCALIFG;          // Clear arbitration lost flag
            break;
    }
}