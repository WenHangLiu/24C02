#include "SysTick.h"
static __IO uint32_t TimingDelay;
/* 
*函数名：SysTick_Init();
 * 描述  : 系统滴答时钟初始化函数
 * 输入  ：无
 * 输出  : 无
 */
// tick常用值
//SystemCoreClock /1000    1ms中断一次
//SystemCoreClock /100000  10us中断一次
//SystemCoreClock /1000000 1us中断一次
void SysTick_Init(void )
{
 if(SysTick_Config (SystemCoreClock /1000000))
 {
	 while(1);
 }
 SysTick ->CTRL &=~SysTick_CTRL_CLKSOURCE_Msk;//关闭系统滴答时钟
}
 /* 
 *函数名:void Delay_us(__IO uint32_t nTime );
 * 描述  : 延时函数
 * 输入  ：延时参数
 * 输出  : 无
 */
//void Delay_us(__IO uint32_t nTime )
//{
// 
// TimingDelay=nTime;
// SysTick->CTRL |=SysTick_CTRL_ENABLE_Msk ;//开启系统滴答时钟
// while(TimingDelay!=0);
//}
void Delay_us(__IO uint32_t nTime )
{
 
 TimingDelay=nTime;
 SysTick->CTRL |=SysTick_CTRL_ENABLE_Msk ;//开启系统滴答时钟
 while(TimingDelay!=0);
}
 /* 
 * 函数名：TimingDelay_Decrement()
 * 描述  : 中断处理函数
 * 输入  ：无
 * 输出  : 无
 */
void TimingDelay_Decrement(void)
{
	 if(TimingDelay!=0x00)
	 {
		 TimingDelay-=1;
	 }
}

