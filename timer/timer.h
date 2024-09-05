/**
 * @file timer.h
 * @brief Timer and PWM driver interface for STM8S003F3
 *
 * This file contains the declarations of Timer and PWM functions, types, and definitions
 * for initializing, configuring, and controlling timers and PWM outputs
 * on the STM8S003F3 microcontroller.
 */

#ifndef __TIMER_H
#define __TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Enumeration of available timers
 */
typedef enum {
  TIMER_1,
  TIMER_2,
} TIMER_IDX;

/**
 * @brief Enumeration of timer operation results
 */
typedef enum {
  TIMER_RESULT_OK,
  TIMER_RESULT_INVALID_TIMER,
  TIMER_RESULT_INVALID_PARAM,
  TIMER_RESULT_INVALID_PRIORITY,
  TIMER_RESULT_INVALID_CHANNEL,
  TIMER_RESULT_ERROR
} TIMER_Result;

/**
 * @brief Timer counter variables
 * 
 * These variables are incremented in the respective timer interrupt handlers.
 */
extern volatile uint32_t g_T1count, g_T2count;

/**
 * @brief Initialize a timer
 *
 * @param tmNo Timer number (TIMER_1 or TIMER_2)
 * @param prescale Timer prescaler value
 * @param period Timer period value
 * @param repeat Number of timer repeats (0 for continuous)
 * @return TIMER_Result Result of the operation
 */
TIMER_Result Timer_Init(TIMER_IDX tmNo, uint16_t prescale, uint16_t period, uint8_t repeat);

/**
 * @brief Start or stop a timer
 *
 * @param tmNo Timer number (TIMER_1 or TIMER_2)
 * @param enable TRUE to start the timer, FALSE to stop
 * @return TIMER_Result Result of the operation
 */
TIMER_Result Timer_Start(TIMER_IDX tmNo, bool enable);

/**
 * @brief Reset a timer's counter
 *
 * @param tmNo Timer number (TIMER_1 or TIMER_2)
 * @return TIMER_Result Result of the operation
 */
TIMER_Result Timer_Reset(TIMER_IDX tmNo);

/**
 * @brief Set a timer's counter value
 *
 * @param tmNo Timer number (TIMER_1 or TIMER_2)
 * @param val Value to set the counter to
 * @return TIMER_Result Result of the operation
 */
TIMER_Result Timer_SetCounter(TIMER_IDX tmNo, uint16_t val);

/**
 * @brief Configure timer interrupt
 *
 * @param tmNo Timer number (TIMER_1 or TIMER_2)
 * @param priority Interrupt priority (0-3)
 * @return TIMER_Result Result of the operation
 */
TIMER_Result TimerIntConfig(TIMER_IDX tmNo, uint8_t priority);

#ifdef __cplusplus
}
#endif

#endif // __TIMER_H