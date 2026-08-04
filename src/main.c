#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include "matrix15.h"
#include "pps.h"
#include "mpu6050.h"
#include "uart_benchmark.h"
#include "sdcard.h"

int main(void)
{
    printk("Zephyr Benchmark Suite\n");

    matrix_start();
    pps_start();
    mpu6050_start();
    uart_benchmark_start();
    sdcard_start();

    while (1) {
        k_sleep(K_FOREVER);
    }

    return 0;
}
