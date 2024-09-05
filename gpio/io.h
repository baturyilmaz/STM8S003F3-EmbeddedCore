/**
 * @file io.h
 * @brief GPIO (General Purpose Input/Output) driver interface for STM8S003F3
 *
 * This file contains the declarations of GPIO functions, types, and definitions
 * for initializing, configuring, and controlling GPIO pins on the STM8S003F3 microcontroller.
 */

#ifndef __IO_H
#define __IO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm8s.h"

/**
 * @brief Enumeration of GPIO modes
 */
typedef enum {
  IO_MODE_INPUT = GPIO_MODE_IN_FL_NO_IT,
  IO_MODE_INPUT_PU = GPIO_MODE_IN_PU_NO_IT,
  IO_MODE_OUTPUT = GPIO_MODE_OUT_PP_LOW_FAST,
  IO_MODE_OUTPUT_OD = GPIO_MODE_OUT_OD_LOW_FAST,
  IO_MODE_OUTPUT_PP_HIGH = GPIO_MODE_OUT_PP_HIGH_FAST,
} IO_MODE;

/**
 * @brief Enumeration of IO pin indices
 */
typedef enum {
  IOP_LED,
  
  // UART
  IOP_U1RX,
  IOP_U1TX,
  
  // ADC
  IOP_AIN2,
  
  // PWM
  IOP_PWM2,

  // Add other IO pins as needed

  IO_IDX_MAX  // Keep this as the last item
} IO_IDX;

/**
 * @brief Structure to hold IO pin information
 */
typedef struct {
  GPIO_TypeDef* port;
  GPIO_Pin_TypeDef pin;
} IO_PIN;

/**
 * @brief Enumeration of IO operation results
 */
typedef enum {
  IO_RESULT_OK,
  IO_RESULT_INVALID_PIN,
  IO_RESULT_INVALID_PARAM,
  IO_RESULT_ERROR
} IO_Result;

#ifdef _IOS_
extern IO_PIN _ios[];
#else
extern IO_PIN _ios[];
#endif

/**
 * @brief Initialize a GPIO pin
 * @param idx The index of the IO pin to initialize
 * @param mode The mode to set for the IO pin
 * @return IO_Result The result of the operation
 */
IO_Result IO_Init(IO_IDX idx, IO_MODE mode);

/**
 * @brief Write a value to a GPIO pin
 * @param idx The index of the IO pin to write to
 * @param val The value to write (0 for low, non-zero for high)
 * @return IO_Result The result of the operation
 */
IO_Result IO_Write(IO_IDX idx, int val);

/**
 * @brief Read the value of a GPIO pin
 * @param idx The index of the IO pin to read from
 * @param pValue Pointer to store the read value (0 for low, 1 for high)
 * @return IO_Result The result of the operation
 */
IO_Result IO_Read(IO_IDX idx, int* pValue);

/**
 * @brief Toggle the state of a GPIO pin
 * @param idx The index of the IO pin to toggle
 * @return IO_Result The result of the operation
 */
IO_Result IO_Toggle(IO_IDX idx);

#ifdef __cplusplus
}
#endif

#endif // __IO_H