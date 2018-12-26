#ifndef _SYSTICK_H_
#define _SYSTICK_H_
#include "stm32f10x.h"

void SysTick_Init(void );//初始化
void Delay_us(__IO uint32_t  nTime);//延时函数，延时10us
#define Delay_ms(x) Delay_us(100*x)//延时1ms
#endif
