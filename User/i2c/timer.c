#include "timer.h"
#include "dht11.h"
#include "oled.h"
extern void DHT11Read(uint8_t*Data_Array);
uint8_t Data_Array[5];
 u8 temperature;  	    
 u8 humidity; 
	extern u8 Hightemp ;//extern 用法：在原C文件中直接定义全局变量，在需要用其变量的另外C文件加extern
	extern u8 Lowtemp ;
	extern u8 Highhumi ;
	extern u8 Lowhumi ; 
//void TIM1_Int_Init(u16 arr,u16 psc)
//{
//  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;

//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //时钟使能
//	
//	//定时器TIM1初始化
//	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
//	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
//	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//注意此为重复溢出0 在用TIM1时一定要加
//	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
// 
//	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE ); //使能指定的TIM1中断,允许更新中断

//	//中断优先级NVIC设置
//	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  //TIM1中断
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //从优先级0级
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
//	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


//	TIM_Cmd(TIM1, ENABLE);  //使能TIMx					 
//}
////定时器1中断服务程序
//void TIM1_IRQHandler(void)   //TIM1中断
//{
//	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)  //检查TIM1更新中断发生与否
//		{
//		TIM_ClearITPendingBit(TIM1, TIM_IT_Update  );  //清除TIMx更新中断标志 
////执行程序
//		DHT11_Read_Data(&temperature,&humidity);		//读取温湿度值
////		OLED_Print(10,2,"湿度");
////		OLED_Print(10,0,"温度");	
//		OLED_Printf(45,0,":%d" ,temperature);	
//		OLED_Printf(45,2,":%d" ,humidity);
//		if(temperature>=Hightemp)
//	{
// 	GPIO_SetBits(GPIOB,GPIO_Pin_8);		
//	GPIO_ResetBits(GPIOB,GPIO_Pin_9);
//		
//	}
//	else 
//	{
//		GPIO_ResetBits(GPIOB,GPIO_Pin_8);				
//		GPIO_SetBits(GPIOB,GPIO_Pin_9);	
//	
//	}		
//			
//		}
//}


void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


	TIM_Cmd(TIM3, ENABLE);  //使能TIMx					 
}
//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
//执行程序
		DHT11_Read_Data(&temperature,&humidity);		//读取温湿度值
		OLED_Print(10,2,"湿度");
		OLED_Print(10,0,"温度");	
		OLED_Printf(45,0,":%d" ,temperature);	
		OLED_Printf(45,2,":%d" ,humidity);
		if(temperature>=Hightemp)
	{
 	GPIO_SetBits(GPIOB,GPIO_Pin_8);		
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);
		
	}
	else 
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_8);				
		GPIO_SetBits(GPIOB,GPIO_Pin_9);	
	
	}				
		}
}

