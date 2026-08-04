#include "timer2.h"

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <stm32f4xx.h>
#include <zephyr/irq.h>
#include <zephyr/sys/util.h>
static volatile uint32_t last_capture = 0;

uint32_t timer2_get_capture(void)
{
    return last_capture;
}
static void tim2_isr(const void *arg)
{
    ARG_UNUSED(arg);

    if (TIM2->SR & TIM_SR_CC1IF)
    {
        last_capture = TIM2->CCR1;

        TIM2->SR &= ~TIM_SR_CC1IF;

        k_sem_give(&pps_sem);
    }
}
void timer2_input_capture_init(void)
{
    /* Enable peripheral clocks */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    /* Configure PA0 as AF1 (TIM2_CH1) */
    GPIOA->MODER &= ~(3U << 0);
    GPIOA->MODER |=  (2U << 0);

    GPIOA->AFR[0] &= ~(0xFU << 0);
    GPIOA->AFR[0] |=  (1U << 0);

    /* Timer configuration */
    TIM2->CR1 = 0;

    TIM2->PSC = 95;
    TIM2->ARR = 0xFFFFFFFF;

    /* Load PSC immediately */
    TIM2->EGR = TIM_EGR_UG;

    /* Channel 1 input capture */
    TIM2->CCMR1 = 0;
    TIM2->CCMR1 |= TIM_CCMR1_CC1S_0;

    /* Rising edge */
    TIM2->CCER = 0;

    /* ******** MISSING IN YOUR CODE ******** */
    /* Enable Capture Channel 1 */
    TIM2->CCER |= TIM_CCER_CC1E;

    /* Clear pending flags */
    TIM2->SR = 0;

    /* Enable capture interrupt */
    TIM2->DIER |= TIM_DIER_CC1IE;

    IRQ_CONNECT(
     TIM2_IRQn,
     0,
     tim2_isr,
     NULL,
     0);

   irq_enable(TIM2_IRQn);

    /* Start timer */
    TIM2->CR1 |= TIM_CR1_CEN;

    printk("TIM2 Initialized\n");
}


