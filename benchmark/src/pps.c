#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include "pps.h"
#include "timer2.h"

#define PPS_STACK_SIZE 1024
#define PPS_PRIORITY   4

K_SEM_DEFINE(pps_sem, 0, 1);

K_THREAD_STACK_DEFINE(pps_stack, PPS_STACK_SIZE);
static struct k_thread pps_thread;

static void pps_thread_fn(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1);
    ARG_UNUSED(p2);
    ARG_UNUSED(p3);

    while (1) {
        k_sem_take(&pps_sem, K_FOREVER);
    }
}

void pps_start(void)
{
    timer2_input_capture_init();

    k_thread_create(&pps_thread,
                    pps_stack,
                    K_THREAD_STACK_SIZEOF(pps_stack),
                    pps_thread_fn,
                    NULL,
                    NULL,
                    NULL,
                    PPS_PRIORITY,
                    0,
                    K_NO_WAIT);
}
