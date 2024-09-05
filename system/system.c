#include "stm8s.h"
#include "system.h"

static volatile clock_t _TmTick = 0;

void Sys_IoInit()
{

}

void Sys_ClockInit(void)
{
//  CLK_DeInit();
  
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
  
//  CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
}

void Sys_TickInit(void)
{
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, ENABLE);
  
  TIM4_TimeBaseInit(TIM4_PRESCALER_128, 124); // 16 MHz / 128 / 125 = 1kHz
  TIM4_ClearFlag(TIM4_FLAG_UPDATE);
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
  TIM4_Cmd(ENABLE);  
}

void Sys_ClockTick(void)
{
  ++_TmTick;
}

clock_t clock(void)
{
  return _TmTick;
}

void DelayMs(uint16_t ms)
{
  clock_t start = clock();
  while (clock() - start < ms);
}