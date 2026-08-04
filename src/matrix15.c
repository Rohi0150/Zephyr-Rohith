#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include "matrix15.h"

#define MATRIX_STACK_SIZE 2048
#define MATRIX_PRIORITY   5

K_THREAD_STACK_DEFINE(matrix_stack, MATRIX_STACK_SIZE);
static struct k_thread matrix_thread;

void matrix_thread_fn(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1);
    ARG_UNUSED(p2);
    ARG_UNUSED(p3);

    uint64_t start;
    uint64_t end;
    uint64_t cycles;
    uint64_t time_us;

    uint64_t min_cy = UINT64_MAX;
    uint64_t max_cy = 0;
    uint64_t total_cycles = 0;
    uint64_t iteration = 0;

    while (1)
    {
        start = k_cycle_get_64();

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                C[i][j] = 0.0f;

                for (int k = 0; k < N; k++)
                {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }

        end = k_cycle_get_64();

        cycles = end - start;
        time_us = k_cyc_to_us_floor64(cycles);

        iteration++;
        total_cycles += cycles;

        if (cycles < min_cy)
            min_cy = cycles;

        if (cycles > max_cy)
            max_cy = cycles;

        printk("\n========== MATRIX BENCHMARK ==========\n");
        printk("Iteration : %llu\n", iteration);
        printk("Cycles    : %llu\n", cycles);
        printk("Time      : %llu us\n", time_us);
        printk("Minimum   : %llu\n", min_cy);
        printk("Maximum   : %llu\n", max_cy);
        printk("Average   : %llu\n", total_cycles / iteration);

        k_sleep(K_SECONDS(1));
    }
}

void matrix_start(void)
{
    k_thread_create(&matrix_thread,
                    matrix_stack,
                    K_THREAD_STACK_SIZEOF(matrix_stack),
                    matrix_thread_fn,
                    NULL,
                    NULL,
                    NULL,
                    MATRIX_PRIORITY,
                    0,
                    K_NO_WAIT);
}
