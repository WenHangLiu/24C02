#ifndef _SYSTICK_H_
#define _SYSTICK_H_
#include "stm32f10x.h"

void SysTick_Init(void );//��ʼ��
void Delay_us(__IO uint32_t  nTime);//��ʱ��������ʱ10us
#define Delay_ms(x) Delay_us(100*x)//��ʱ1ms
#endif
