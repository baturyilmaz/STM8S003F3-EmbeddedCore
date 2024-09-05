/**
 * @file uart.c
 * @brief UART driver implementation for STM8S003F3
 *
 * This file contains the implementation of UART functions for initializing,
 * configuring, and performing UART operations on the STM8S003F3 microcontroller.
 */

#include <stdio.h>
#include <stdarg.h>
#include "stm8s.h"
#include "uart.h"
#include "io.h"
#include "system.h"

/**
 * @brief Initialize UART
 *
 * @param idx UART index (currently only UART_1 is supported)
 * @param baud Baud rate for UART communication
 * @return UART_Result Result of the operation
 */
UART_Result UART_Init(UART_IDX idx, int baud)
{
    if (idx != UART_1) {
        return UART_RESULT_INVALID_UART;
    }

    // Enable UART clock
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_UART1, ENABLE);
    
    // Configure UART pins
    IO_Init(IOP_U1TX, IO_MODE_OUTPUT_PP_HIGH);    // UART1_TX // push-pull
    IO_Init(IOP_U1RX, IO_MODE_INPUT);             // UART1_RX // input-floating
    
    // Configure UART
    UART1_DeInit();
    UART1_Init((int)baud, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, 
               UART1_PARITY_NO, UART1_SYNCMODE_CLOCK_DISABLE, 
               UART1_MODE_TXRX_ENABLE);
    
    // Start UART Peripheral
    UART1_Cmd(ENABLE);

    return UART_RESULT_OK;
}

/**
 * @brief Send a single character over UART
 *
 * @param idx UART index (currently only UART_1 is supported)
 * @param ch Character to send
 * @return UART_Result Result of the operation
 */
UART_Result UART_Send(UART_IDX idx, unsigned char ch)
{
    if (idx != UART_1) {
        return UART_RESULT_INVALID_UART;
    }

    while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
    UART1_SendData8(ch);

    return UART_RESULT_OK;
}

/**
 * @brief Check if there's data available in the UART receive buffer
 *
 * @param idx UART index (currently only UART_1 is supported)
 * @return int 1 if data is available, 0 otherwise
 */
int UART_ChkRxBuff(UART_IDX idx)
{
    if (idx != UART_1) {
        return 0;
    }

    return UART1_GetFlagStatus(UART1_FLAG_RXNE) != RESET;
}

/**
 * @brief Receive a single character from UART
 *
 * @param idx UART index (currently only UART_1 is supported)
 * @param pc Pointer to store the received character
 * @return UART_Result Result of the operation
 */
UART_Result UART_Recv(UART_IDX idx, unsigned char *pc)
{
    if (idx != UART_1 || pc == NULL) {
        return UART_RESULT_INVALID_PARAM;
    }

    while (!UART_ChkRxBuff(idx));
    
    if (UART1_GetFlagStatus(UART1_FLAG_OR) != RESET)
        return UART_RESULT_OVERRUN;
    if (UART1_GetFlagStatus(UART1_FLAG_NF) != RESET)
        return UART_RESULT_NOISE;
    if (UART1_GetFlagStatus(UART1_FLAG_FE) != RESET)
        return UART_RESULT_FRAMING;
    if (UART1_GetFlagStatus(UART1_FLAG_PE) != RESET)
        return UART_RESULT_PARITY;
    
    *pc = UART1_ReceiveData8();
    
    return UART_RESULT_OK;
}

/**
 * @brief Send a single character over the console UART
 *
 * @param c Character to send
 */
void UART_putch(unsigned char c)
{
    if (c == '\n')
    {
        UART_Send(CON_UART, '\n');
        UART_Send(CON_UART, '\r');
    }
    else
    {
        UART_Send(CON_UART, c);
    }
}

/**
 * @brief Send a string over UART
 *
 * @param str String to send
 * @param size Number of characters to send
 * @return int Number of characters sent
 */
int UART_puts(const char *str, int size)
{
    int i = 0;
    while (i < size)
    {
        UART_putch(str[i++]);
    }
    
    return i;
}

/**
 * @brief Send a null-terminated string over UART
 *
 * @param str Null-terminated string to send
 * @return int Number of characters sent
 */
int UART_puts1(const char *str)
{
    int i = 0;
    
    while (str[i])
    {
        UART_putch(str[i++]);
    }
    
    return i;
}

/**
 * @brief Send formatted output over UART
 *
 * @param fmt Format string
 * @param ... Variable arguments
 * @return int Number of characters sent
 */
int UART_printf(const char *fmt, ...)
{
    va_list args;
    static char str[32];
    int size;
    
    va_start(args, fmt);
    size = vsnprintf(str, sizeof(str), fmt, args);
    va_end(args);
    
    return UART_puts1(str);
}