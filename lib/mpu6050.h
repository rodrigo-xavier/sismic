#pragma once
#include <msp430.h>
#include <stdint.h>
#include "i2c.h"

#define MPU6050_ADDRESS_AD0_LOW     0x68 // address pin low (GND), default for InvenSense evaluation board

#define MPU6050_RA_SMPLRT_DIV       0x19 // Sample rate divider register address
#define MPU6050_RA_CONFIG           0x1A // Configuration register address
#define MPU6050_RA_GYRO_CONFIG      0x1B // Gyroscope configuration register address
#define MPU6050_RA_ACCEL_CONFIG     0x1C // Accelerometer configuration register address
#define MPU6050_RA_PWR_MGMT_1       0x6B // Power management 1 register address

#define MPU6050_RA_ACCEL_XOUT_H     0x3B
#define MPU6050_RA_ACCEL_XOUT_L     0x3C
#define MPU6050_RA_ACCEL_YOUT_H     0x3D
#define MPU6050_RA_ACCEL_YOUT_L     0x3E
#define MPU6050_RA_ACCEL_ZOUT_H     0x3F
#define MPU6050_RA_ACCEL_ZOUT_L     0x40

#define MPU6050_RA_GYRO_XOUT_H      0x43
#define MPU6050_RA_GYRO_XOUT_L      0x44
#define MPU6050_RA_GYRO_YOUT_H      0x45
#define MPU6050_RA_GYRO_YOUT_L      0x46
#define MPU6050_RA_GYRO_ZOUT_H      0x47
#define MPU6050_RA_GYRO_ZOUT_L      0x48


void init_mpu6050(void);
void read_mpu6050(int16_t *accel_x, int16_t *accel_y, int16_t *accel_z, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z);


void init_mpu6050(void)
{
    // Configure MPU6050
    i2c_write_register(MPU6050_RA_PWR_MGMT_1, 0x00);   // Wake up MPU6050
    i2c_write_register(MPU6050_RA_SMPLRT_DIV, 0x07);   // Set sample rate to 1 kHz
    i2c_write_register(MPU6050_RA_CONFIG, 0x00);       // Set DLPF to 260 Hz bandwidth
    i2c_write_register(MPU6050_RA_GYRO_CONFIG, 0x08);  // Set gyro full scale
    i2c_write_register(MPU6050_RA_ACCEL_CONFIG, 0x08); // Set accelerometer full scale
}

void read_mpu6050(int16_t *accel_x, int16_t *accel_y, int16_t *accel_z, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z)
{
    // Read MPU6050 data
    *accel_x = (i2c_read_register(MPU6050_RA_ACCEL_XOUT_H) << 8) | i2c_read_register(MPU6050_RA_ACCEL_XOUT_L);
    *accel_y = (i2c_read_register(MPU6050_RA_ACCEL_YOUT_H) << 8) | i2c_read_register(MPU6050_RA_ACCEL_YOUT_L);
    *accel_z = (i2c_read_register(MPU6050_RA_ACCEL_ZOUT_H) << 8) | i2c_read_register(MPU6050_RA_ACCEL_ZOUT_L);
    *gyro_x = (i2c_read_register(MPU6050_RA_GYRO_XOUT_H) << 8) | i2c_read_register(MPU6050_RA_GYRO_XOUT_L);
    *gyro_y = (i2c_read_register(MPU6050_RA_GYRO_YOUT_H) << 8) | i2c_read_register(MPU6050_RA_GYRO_YOUT_L);
    *gyro_z = (i2c_read_register(MPU6050_RA_GYRO_ZOUT_H) << 8) | i2c_read_register(MPU6050_RA_GYRO_ZOUT_L);
}
