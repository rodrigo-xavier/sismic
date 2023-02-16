#include "../../lib/l298n.h"
#include "../../lib/mpu6050.h"
#include "../../lib/i2c.h"
#include <msp430.h>


// int main(void)
// {
//    int16_t accel_x, accel_y, accel_z, gyro_x, gyro_y, gyro_z;

//    WDTCTL = WDTPW + WDTHOLD;

//    init_l298n();   // Configura o módulo L298N
//    init_i2c();     // Initialize I2C
//    init_mpu6050(); // Initialize MPU6050
//    forward();
//    // reverse();
//    config_l298n_pwm(0.6);

//    while (1)
//    {
//       read_mpu6050(&accel_x, &accel_y, &accel_z, &gyro_x, &gyro_y, &gyro_z);
//    }
//    return 0;
// }

int main(void)
{
   WDTCTL = WDTPW + WDTHOLD; // Inicializa o PWM

   init_l298n();   // Configura o módulo L298N
   forward();
   config_l298n_pwm(0.6);

   // __delay_cycles(5000);
   // reverse();
   return 0;
}
