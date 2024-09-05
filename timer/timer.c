/**
 * @file timer.c
 * @brief Timer and PWM driver implementation for STM8S003F3
 *
 * This file contains the implementation of Timer and PWM functions for
 * initializing, configuring, and controlling timers and PWM outputs
 * on the STM8S003F3 microcontroller.
 */

#include "stm8s.h"
#include "stm8s_itc.h"
#include "timer.h"
#include "io.h"

/**
 * @brief Initialize a timer
 *
 * @param tmNo Timer number (TIMER_1 or TIMER_2)
 * @param prescale Timer prescaler value
 * @param period Timer period value
 * @param repeat Number of timer repeats (0 for continuous)
 * @return TIMER_Result Result of the operation
 */
TIMER_Result Timer_Init(TIMER_IDX tmNo, uint16_t prescale, uint16_t period, uint8_t repeat)
{
    switch(tmNo)
    {
    case TIMER_1:
        CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER1, ENABLE);
        TIM1_TimeBaseInit(prescale - 1, TIM1_COUNTERMODE_UP, period - 1, repeat - 1);
        break;
    case TIMER_2:
        CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2, ENABLE);
        TIM2_TimeBaseInit(TIM2_PRESCALER_1, period - 1);
        TIM2_PrescalerConfig(prescale - 1, TIM2_PSCRELOADMODE_IMMEDIATE);   
        break;
    default:
        return TIMER_RESULT_INVALID_TIMER;
    }
    
    Timer_Reset(tmNo);
    return TIMER_RESULT_OK;
}

/**
 * @brief Start or stop a timer
 *
 * @param tmNo Timer number (TIMER_1 or TIMER_2)
 * @param enable TRUE to start the timer, FALSE to stop
 * @return TIMER_Result Result of the operation
 */
TIMER_Result Timer_Start(TIMER_IDX tmNo, bool enable)
{
    switch(tmNo)
    {
    case TIMER_1:
        TIM1_Cmd(enable ? ENABLE : DISABLE);
        break;
    case TIMER_2:
        TIM2_Cmd(enable ? ENABLE : DISABLE);
        break;
    default:
        return TIMER_RESULT_INVALID_TIMER;
    }
    return TIMER_RESULT_OK;
}

/**
 * @brief Reset a timer's counter
 *
 * @param tmNo Timer number (TIMER_1 or TIMER_2)
 * @return TIMER_Result Result of the operation
 */
TIMER_Result Timer_Reset(TIMER_IDX tmNo)
{
    switch(tmNo)
    {
    case TIMER_1:
        TIM1_SetCounter(0);
        break;
    case TIMER_2:
        TIM2_SetCounter(0);
        break;
    default:
        return TIMER_RESULT_INVALID_TIMER;
    }
    return TIMER_RESULT_OK;
}

/**
 * @brief Set a timer's counter value
 *
 * @param tmNo Timer number (TIMER_1 or TIMER_2)
 * @param val Value to set the counter to
 * @return TIMER_Result Result of the operation
 */
TIMER_Result Timer_SetCounter(TIMER_IDX tmNo, uint16_t val)
{
    switch(tmNo)
    {
    case TIMER_1:
        TIM1_SetCounter(val);
        break;
    case TIMER_2:
        TIM2_SetCounter(val);
        break;
    default:
        return TIMER_RESULT_INVALID_TIMER;
    }
    return TIMER_RESULT_OK;
}

/**
 * @brief Configure timer interrupt
 *
 * @param tmNo Timer number (TIMER_1 or TIMER_2)
 * @param priority Interrupt priority (0-3)
 * @return TIMER_Result Result of the operation
 */
TIMER_Result TimerIntConfig(TIMER_IDX tmNo, uint8_t priority)
{
    if (priority > 3) {
        return TIMER_RESULT_INVALID_PRIORITY;
    }

    switch(tmNo)
    {
    case TIMER_1:
        TIM1_ClearITPendingBit(TIM1_IT_UPDATE);
        TIM1_ITConfig(TIM1_IT_UPDATE, ENABLE);
        ITC_SetSoftwarePriority(ITC_IRQ_TIM1_OVF, (ITC_PriorityLevel_TypeDef)priority);
        break;
    case TIMER_2:
        TIM2_ClearITPendingBit(TIM2_IT_UPDATE);
        TIM2_ITConfig(TIM2_IT_UPDATE, ENABLE);
        ITC_SetSoftwarePriority(ITC_IRQ_TIM2_OVF, (ITC_PriorityLevel_TypeDef)priority);
        break;
    default:
        return TIMER_RESULT_INVALID_TIMER;
    }
    return TIMER_RESULT_OK;
}
