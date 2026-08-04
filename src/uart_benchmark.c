#include <zephyr/kernel.h>

#include "uart_benchmark.h"

#define UART_STACK_SIZE 1024
#define UART_PRIORITY   6

K_THREAD_STACK_DEFINE(uart_stack, UART_STACK_SIZE);
static struct k_thread uart_thread;

static void uart_thread_fn(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1);
    ARG_UNUSED(p2);
    ARG_UNUSED(p3);

    while (1) {
        k_sleep(K_MSEC(100));
    }
}

void uart_benchmark_start(void)
{
    k_thread_create(&uart_thread,
                    uart_stack,
                    K_THREAD_STACK_SIZEOF(uart_stack),
                    uart_thread_fn,
                    NULL,
                    NULL,
                    NULL,
                    UART_PRIORITY,
                    0,
                    K_NO_WAIT);
}
