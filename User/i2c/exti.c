#include "key.h"
#include "exti.h"
#include "delay.h"
#include "oled.h"
void EXTIX_Init(void)
{
	 EXTI_InitTypeDef EXTI_InitInstruct;
	 NVIC_InitTypeDef NVIC_InitStructure;
	
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource11);
   GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource10);
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
	
	EXTI_InitInstruct.EXTI_Line=EXTI_Line11;
	EXTI_InitInstruct.EXTI_LineCmd=ENABLE;
	EXTI_InitInstruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitInstruct.EXTI_Trigger=EXTI_Trigger_Falling;
 	EXTI_Init(&EXTI_InitInstruct);
	
	EXTI_InitInstruct.EXTI_Line=EXTI_Line10;
	EXTI_InitInstruct.EXTI_LineCmd=ENABLE;
	EXTI_InitInstruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitInstruct.EXTI_Trigger=EXTI_Trigger_Falling;
 	EXTI_Init(&EXTI_InitInstruct);
	
	EXTI_InitInstruct.EXTI_Line=EXTI_Line1;
	EXTI_InitInstruct.EXTI_LineCmd=ENABLE;
	EXTI_InitInstruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitInstruct.EXTI_Trigger=EXTI_Trigger_Falling;
 	EXTI_Init(&EXTI_InitInstruct);
	
	EXTI_InitInstruct.EXTI_Line=EXTI_Line0;
	EXTI_InitInstruct.EXTI_LineCmd=ENABLE;
	EXTI_InitInstruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitInstruct.EXTI_Trigger=EXTI_Trigger_Falling;
 	EXTI_Init(&EXTI_InitInstruct);	
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//抢占优先级 越小越优先
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_InitStructure);
}
void EXTI1_IRQHandler(void)
{
   delay_ms(10);
   if (!Key_Scan(GPIOB,GPIO_Pin_1))
   {  
//执行下面程序
	OLED_clear(); 
   }
//	 else ;
	 EXTI_ClearITPendingBit(EXTI_Line1);
}
void EXTI0_IRQHandler(void)
{
   delay_ms(10);
   if (!Key_Scan(GPIOB,GPIO_Pin_0))
   {  
//执行下面程序
		OLED_Print(10,4,"刘文航"); 
   }
//	 else ;	 
	 EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI15_10_IRQHandler(void)
{
   delay_ms(10);
   if (!Key_Scan(GPIOB,GPIO_Pin_10))
   {  
//执行下面程序
		OLED_Print(10,4,"刘文航"); 
   }
	 EXTI_ClearITPendingBit(EXTI_Line10);
}

