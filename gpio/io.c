/**
 * @file io.c
 * @brief GPIO (General Purpose Input/Output) driver implementation for STM8S003F3
 *
 * This file contains the implementation of GPIO functions for initializing,
 * reading, writing, and toggling GPIO pins on the STM8S003F3 microcontroller.
 */

#define _IOS_
#include "stm8s.h"
#include "io.h"

/**
 * @brief Initialize a GPIO pin
 * 
 * @param idx The index of the IO pin to initialize
 * @param mode The mode to set for the IO pin
 * @return IO_Result The result of the operation
 */
IO_Result IO_Init(IO_IDX idx, IO_MODE mode)
{
    if (idx >= IO_IDX_MAX) {
        return IO_RESULT_INVALID_PIN;
    }

    GPIO_Init(_ios[idx].port, _ios[idx].pin, (GPIO_Mode_TypeDef)mode);
    return IO_RESULT_OK;
}

/**
 * @brief Write a value to a GPIO pin
 * 
 * @param idx The index of the IO pin to write to
 * @param val The value to write (0 for low, non-zero for high)
 * @return IO_Result The result of the operation
 */
IO_Result IO_Write(IO_IDX idx, int val)
{
    if (idx >= IO_IDX_MAX) {
        return IO_RESULT_INVALID_PIN;
    }

    if (val)
        GPIO_WriteHigh(_ios[idx].port, _ios[idx].pin);
    else
        GPIO_WriteLow(_ios[idx].port, _ios[idx].pin);

    return IO_RESULT_OK;
}

/**
 * @brief Read the value of a GPIO pin
 * 
 * @param idx The index of the IO pin to read from
 * @param pValue Pointer to store the read value (0 for low, 1 for high)
 * @return IO_Result The result of the operation
 */
IO_Result IO_Read(IO_IDX idx, int* pValue)
{
    if (idx >= IO_IDX_MAX || pValue == NULL) {
        return IO_RESULT_INVALID_PARAM;
    }

    *pValue = GPIO_ReadInputPin(_ios[idx].port, _ios[idx].pin);
    return IO_RESULT_OK;
}

/**
 * @brief Toggle the state of a GPIO pin
 * 
 * @param idx The index of the IO pin to toggle
 * @return IO_Result The result of the operation
 */
IO_Result IO_Toggle(IO_IDX idx)
{
    if (idx >= IO_IDX_MAX) {
        return IO_RESULT_INVALID_PIN;
    }

    int currentValue;
    IO_Result result = IO_Read(idx, &currentValue);
    if (result != IO_RESULT_OK) {
        return result;
    }

    return IO_Write(idx, !currentValue);
}
