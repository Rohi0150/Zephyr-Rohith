#ifndef TIMER2_H
#define TIMER2_H

#include <zephyr/kernel.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Semaphore defined in main.c */
extern struct k_sem pps_sem;

/* Initialize TIM2 Input Capture on PA0 (TIM2_CH1) */
void timer2_input_capture_init(void);

/* Return the latest captured timer value */
uint32_t timer2_get_capture(void);

#ifdef __cplusplus
}
#endif

#endif /* TIMER2_H */
