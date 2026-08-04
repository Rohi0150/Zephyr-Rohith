#ifndef MPU6050_H
#define MPU6050_H

#include <stdint.h>

void mpu6050_init(void);
uint64_t mpu6050_read(uint8_t *imu_data);

void mpu6050_start(void);

#endif /* MPU6050_H */
