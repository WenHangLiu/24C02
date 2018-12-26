#include "SysTick.h"
static __IO uint32_t TimingDelay;
/* 
*��������SysTick_Init();
 * ����  : ϵͳ�δ�ʱ�ӳ�ʼ������
 * ����  ����
 * ���  : ��
 */
// tick����ֵ
//SystemCoreClock /1000    1ms�ж�һ��
//SystemCoreClock /100000  10us�ж�һ��
//SystemCoreClock /1000000 1us�ж�һ��
void SysTick_Init(void )
{
 if(SysTick_Config (SystemCoreClock /1000000))
 {
	 while(1);
 }
 SysTick ->CTRL &=~SysTick_CTRL_CLKSOURCE_Msk;//�ر�ϵͳ�δ�ʱ��
}
 /* 
 *������:void Delay_us(__IO uint32_t nTime );
 * ����  : ��ʱ����
 * ����  ����ʱ����
 * ���  : ��
 */
//void Delay_us(__IO uint32_t nTime )
//{
// 
// TimingDelay=nTime;
// SysTick->CTRL |=SysTick_CTRL_ENABLE_Msk ;//����ϵͳ�δ�ʱ��
// while(TimingDelay!=0);
//}
void Delay_us(__IO uint32_t nTime )
{
 
 TimingDelay=nTime;
 SysTick->CTRL |=SysTick_CTRL_ENABLE_Msk ;//����ϵͳ�δ�ʱ��
 while(TimingDelay!=0);
}
 /* 
 * ��������TimingDelay_Decrement()
 * ����  : �жϴ�����
 * ����  ����
 * ���  : ��
 */
void TimingDelay_Decrement(void)
{
	 if(TimingDelay!=0x00)
	 {
		 TimingDelay-=1;
	 }
}

