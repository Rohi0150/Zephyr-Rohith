#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/i2c.h>

#include "mpu6050.h"

#define MPU_STACK_SIZE 1024
#define MPU_PRIORITY   3

K_SEM_DEFINE(mpu_sem, 0, 1);

K_THREAD_STACK_DEFINE(mpu_stack, MPU_STACK_SIZE);
static struct k_thread mpu_thread;

static void mpu_thread_fn(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1);
    ARG_UNUSED(p2);
    ARG_UNUSED(p3);

    while (1) {
        k_sem_take(&mpu_sem, K_FOREVER);
    }
}

void mpu6050_init(void)
{
}

uint64_t mpu6050_read(uint8_t *imu_data)
{
    ARG_UNUSED(imu_data);
    return 0;
}

void mpu6050_start(void)
{
    mpu6050_init();

    k_thread_create(&mpu_thread,
                    mpu_stack,
                    K_THREAD_STACK_SIZEOF(mpu_stack),
                    mpu_thread_fn,
                    NULL,
                    NULL,
                    NULL,
                    MPU_PRIORITY,
                    0,
                    K_NO_WAIT);
}
