#ifndef __SYSTEM_H
#define __SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

#define HSI_FREQUENCY   16000000 // 16 MHz
#define CLOCKS_PER_SEC  1000 // 1 kHz tick
  
#define CON_UART        UART_1

typedef uint32_t clock_t;

void Sys_ClockInit();
void Sys_IoInit();
void Sys_TickInit();

clock_t clock(void);
void DelayMs(uint16_t ms);

#ifdef __cplusplus
}
#endif

#endif // __SYSTEM_H