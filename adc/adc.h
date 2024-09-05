/**
 * @file adc.h
 * @brief ADC (Analog-to-Digital Converter) driver interface for STM8S003F3
 *
 * This file contains the declarations of ADC functions and definitions
 * for initializing, configuring, and performing analog-to-digital conversions
 * on the STM8S003F3 microcontroller.
 */

#ifndef __ADC_H
#define __ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "io.h"  // For IO_IDX type

/**
 * @brief ADC reference voltage
 * 
 * This value represents the voltage corresponding to the maximum ADC reading.
 * It can be adjusted through calibration.
 */
extern float g_yRef;

/**
 * @brief ADC maximum digital value
 * 
 * This value represents the maximum digital reading of the ADC.
 * For a 10-bit ADC, this is typically 1023.
 */
extern int g_xRef;

/**
 * @brief Initialize ADC IO pin
 * @param idx IO index of the ADC pin
 */
void AY_ADC_IOInit(IO_IDX idx);

/**
 * @brief Initialize ADC for single conversion mode
 */
void AY_ADC_Init_Single(void);

/**
 * @brief Start ADC conversion
 */
void AY_ADC_Start(void);

/**
 * @brief Get ADC conversion result
 * @return ADC conversion result (0-1023 for 10-bit ADC)
 */
uint16_t AY_ADC_Result(void);

/**
 * @brief Perform a single ADC conversion
 * @return ADC conversion result (0-1023 for 10-bit ADC)
 */
int AY_ADC_ConvertS(void);

/**
 * @brief Perform multiple ADC conversions and return the average
 * @return Average of multiple ADC conversions (0-1023 for 10-bit ADC)
 */
int AY_ADC_Convert(void);

/**
 * @brief Calibrate ADC reference values
 * @note This function currently sets default values. Implement actual calibration if needed.
 */
void AY_ADC_Calibrate(void);

/**
 * @brief Convert ADC value to voltage
 * @param adcValue Raw ADC value (0-1023 for 10-bit ADC)
 * @return Calculated voltage
 */
float AY_ADC_ToVoltage(int adcValue);

#ifdef __cplusplus
}
#endif

#endif // __ADC_H