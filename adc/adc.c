/**
 * @file adc.c
 * @brief ADC (Analog-to-Digital Converter) driver implementation for STM8S003F3
 *
 * This file contains the implementation of ADC functions for initializing,
 * configuring, and performing analog-to-digital conversions on the STM8S003F3 microcontroller.
 */

#include "stm8s.h"
#include "io.h"
#include "adc.h"

volatile uint8_t g_bEOC = 0;
float g_yRef = 3.3f;
int g_xRef = 1023; // 10-bit ADC

/**
 * @brief Initialize ADC IO pin
 * @param idx IO index of the ADC pin
 */
void AY_ADC_IOInit(IO_IDX idx)
{
    IO_Init(idx, IO_MODE_INPUT);
}

/**
 * @brief Initialize ADC for single conversion mode
 */
void AY_ADC_Init_Single(void)
{
    // Enable ADC clock
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_ADC, ENABLE);
    
    // Initialize ADC
    ADC1_DeInit();
    ADC1_Init(ADC1_CONVERSIONMODE_SINGLE,
              ADC1_CHANNEL_2,
              ADC1_PRESSEL_FCPU_D18,
              ADC1_EXTTRIG_TIM,
              DISABLE,
              ADC1_ALIGN_RIGHT,
              ADC1_SCHMITTTRIG_ALL,
              DISABLE);
    
    // Enable ADC
    ADC1_Cmd(ENABLE);
}

/**
 * @brief Start ADC conversion
 */
void AY_ADC_Start(void)
{
    ADC1_StartConversion();
}

/**
 * @brief Get ADC conversion result
 * @return ADC conversion result (0-1023 for 10-bit ADC)
 */
uint16_t AY_ADC_Result(void)
{
    return ADC1_GetConversionValue();
}

/**
 * @brief Perform a single ADC conversion
 * @return ADC conversion result (0-1023 for 10-bit ADC)
 */
int AY_ADC_ConvertS(void)
{
    // Start conversion
    AY_ADC_Start();
    
    // Wait for End of Conversion
    while (!ADC1_GetFlagStatus(ADC1_FLAG_EOC))
    {
        // Consider adding a timeout mechanism here
    }
    
    return AY_ADC_Result();
}

/**
 * @brief Perform multiple ADC conversions and return the average
 * @return Average of multiple ADC conversions (0-1023 for 10-bit ADC)
 */
int AY_ADC_Convert(void)
{
    uint32_t totRes = 0;
    const int nSamples = 10;
    
    for (int i = 0; i < nSamples; ++i)
    {
        totRes += AY_ADC_ConvertS();
    }
    
    return (int)(totRes / nSamples);
}

/**
 * @brief Calibrate ADC reference values
 * @note This function currently sets default values. Implement actual calibration if needed.
 */
void AY_ADC_Calibrate(void)
{
    // TODO: Implement actual calibration logic if needed
    g_xRef = 1023;  // Default for 10-bit ADC
    g_yRef = 3.3f;  // Default reference voltage
}

/**
 * @brief Convert ADC value to voltage
 * @param adcValue Raw ADC value (0-1023 for 10-bit ADC)
 * @return Calculated voltage
 */
float AY_ADC_ToVoltage(int adcValue)
{
    return (g_yRef / g_xRef) * adcValue;
}