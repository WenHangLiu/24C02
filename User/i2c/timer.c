#include "timer.h"
#include "dht11.h"
#include "oled.h"
extern void DHT11Read(uint8_t*Data_Array);
uint8_t Data_Array[5];
 u8 temperature;  	    
 u8 humidity; 
	extern u8 Hightemp ;//extern �÷�����ԭC�ļ���ֱ�Ӷ���ȫ�ֱ���������Ҫ�������������C�ļ���extern
	extern u8 Lowtemp ;
	extern u8 Highhumi ;
	extern u8 Lowhumi ; 
//void TIM1_Int_Init(u16 arr,u16 psc)
//{
//  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;

//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //ʱ��ʹ��
//	
//	//��ʱ��TIM1��ʼ��
//	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
//	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
//	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
//	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;//ע���Ϊ�ظ����0 ����TIM1ʱһ��Ҫ��
//	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
// 
//	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM1�ж�,��������ж�

//	//�ж����ȼ�NVIC����
//	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  //TIM1�ж�
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  //�����ȼ�0��
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
//	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


//	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIMx					 
//}
////��ʱ��1�жϷ������
//void TIM1_IRQHandler(void)   //TIM1�ж�
//{
//	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)  //���TIM1�����жϷ������
//		{
//		TIM_ClearITPendingBit(TIM1, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
////ִ�г���
//		DHT11_Read_Data(&temperature,&humidity);		//��ȡ��ʪ��ֵ
////		OLED_Print(10,2,"ʪ��");
////		OLED_Print(10,0,"�¶�");	
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

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx					 
}
//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
//ִ�г���
		DHT11_Read_Data(&temperature,&humidity);		//��ȡ��ʪ��ֵ
		OLED_Print(10,2,"ʪ��");
		OLED_Print(10,0,"�¶�");	
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

