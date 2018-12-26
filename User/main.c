  
#include "stm32f10x.h"
#include "bsp_usart1.h"
#include "sys.h"
#include "delay.h"
#include "24c64.h" 
#include "myiic.h"
#include "oled.h"
#include "key.h"
#include "dht11.h"
#include "exti.h"
#include "timer.h"
//extern void DHT11Read(uint8_t*Data_Array);
//uint8_t Data_Array[5];
// u8 temperature;  	    
// u8 humidity; 
//	extern u8 Hightemp ;//extern 用法：在原C文件中直接定义全局变量，在需要用其变量的另外C文件加extern
//	extern u8 Lowtemp ;
//	extern u8 Highhumi ;
//	extern u8 Lowhumi ; 
int main(void)
{
//	u8 t=0;			    
	delay_init();	    	 //延时函数初始化	 	
	OLED_Configuration(); 
	OLED_clear();
	key_gpioinit();
	key_scan();
	Draw_NchuLogo();
	delay_ms(5000);
	OLED_clear();	
	DHT11_Init();
  EXTIX_Init();
//	TIM3_Int_Init(4999,7199);//10Khz的计数频率，计数到5000为500ms  (4999+1)*(7199+1)/72000000=0.5s
	TIM3_Int_Init(999,7199);//10Khz的计数频率，计数到1000为100ms  (999+1)*(7199+1)/72000000=0.1s	
  //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	while(1);

}	

