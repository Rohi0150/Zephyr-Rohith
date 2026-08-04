#include <zephyr/kernel.h>

#include "sdcard.h"

#define SD_STACK_SIZE 2048
#define SD_PRIORITY   7

K_SEM_DEFINE(sd_sem, 0, 1);

K_THREAD_STACK_DEFINE(sd_stack, SD_STACK_SIZE);
static struct k_thread sd_thread;

static void sd_thread_fn(void *p1, void *p2, void *p3)
{
    ARG_UNUSED(p1);
    ARG_UNUSED(p2);
    ARG_UNUSED(p3);

    while (1) {
        k_sem_take(&sd_sem, K_FOREVER);
    }
}

void sdcard_start(void)
{
    k_thread_create(&sd_thread,
                    sd_stack,
                    K_THREAD_STACK_SIZEOF(sd_stack),
                    sd_thread_fn,
                    NULL,
                    NULL,
                    NULL,
                    SD_PRIORITY,
                    0,
                    K_NO_WAIT);
}
