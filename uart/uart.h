/**
 * @file uart.h
 * @brief UART driver interface for STM8S003F3
 *
 * This file contains the declarations of UART functions, types, and definitions
 * for initializing, configuring, and performing UART operations on the STM8S003F3 microcontroller.
 */

#ifndef __UART_H
#define __UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @brief Enumeration of UART indices
 */
typedef enum {
  UART_1,
  // Add other UART indices if needed
} UART_IDX;

/**
 * @brief Enumeration of UART operation results
 */
typedef enum {
  UART_RESULT_OK,
  UART_RESULT_INVALID_UART,
  UART_RESULT_INVALID_PARAM,
  UART_RESULT_OVERRUN,
  UART_RESULT_NOISE,
  UART_RESULT_FRAMING,
  UART_RESULT_PARITY,
  UART_RESULT_ERROR
} UART_Result;

/**
 * @brief Console UART definition
 */
#define CON_UART UART_1

/**
 * @brief Initialize UART
 *
 * @param idx UART index (currently only UART_1 is supported)
 * @param baud Baud rate for UART communication
 * @return UART_Result Result of the operation
 */
UART_Result UART_Init(UART_IDX idx, uint32_t baud);

/**
 * @brief Send a single character over UART
 *
 * @param idx UART index (currently only UART_1 is supported)
 * @param ch Character to send
 * @return UART_Result Result of the operation
 */
UART_Result UART_Send(UART_IDX idx, unsigned char ch);

/**
 * @brief Check if there's data available in the UART receive buffer
 *
 * @param idx UART index (currently only UART_1 is supported)
 * @return int 1 if data is available, 0 otherwise
 */
int UART_ChkRxBuff(UART_IDX idx);

/**
 * @brief Receive a single character from UART
 *
 * @param idx UART index (currently only UART_1 is supported)
 * @param pc Pointer to store the received character
 * @return UART_Result Result of the operation
 */
UART_Result UART_Recv(UART_IDX idx, unsigned char *pc);

/**
 * @brief Send a single character over the console UART
 *
 * @param c Character to send
 */
void UART_putch(unsigned char c);

/**
 * @brief Send a string over UART
 *
 * @param str String to send
 * @param size Number of characters to send
 * @return int Number of characters sent
 */
int UART_puts(const char *str, int size);

/**
 * @brief Send a null-terminated string over UART
 *
 * @param str Null-terminated string to send
 * @return int Number of characters sent
 */
int UART_puts1(const char *str);

/**
 * @brief Send formatted output over UART
 *
 * @param fmt Format string
 * @param ... Variable arguments
 * @return int Number of characters sent
 */
int UART_printf(const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif // __UART_H