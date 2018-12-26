#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "24c64.h"
#include "key.h"
#include "oled.h"
#include "sys.h"
#include "delay.h"

//typedef struct  TEMP
//{
	u8 Hightemp ;
	u8 Lowtemp ;
	u8 Highhumi ;
	u8 Lowhumi ;
//}TEMP;
// TEMP temperature;

 void Delay(__IO u32 nCount)
{
  for(; nCount != 0; nCount--);
}

/* * * * * 端口初始化* * * * */
void key_gpioinit()
{

  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_10|GPIO_Pin_1|GPIO_Pin_0; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 

	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_SetBits(GPIOB, GPIO_Pin_11|GPIO_Pin_10|GPIO_Pin_1|GPIO_Pin_0);	//选 上 退 下
        
}

 u8 Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{			
		/*检测是否有按键按下 */
   	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON ) 
	  {	   
	 	 /*延时消抖*/
	  	Delay(10000);		
	   		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
					{	 
						/*等待按键释放 */
						while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_OFF);   
			 			return 	KEY_ON;	 
					}
			else
					return KEY_OFF;
		}
	else
		return KEY_OFF;
}
/* * * * * 键盘扫描 * * * */
//先读取E2PROM中的值,然后进入键盘扫描,确认退出键盘扫描后
//把值赋给变量,再把修改后的值写入E2PROM
void key_scan()
{
	
    u8 mainkey=1,numflag=0,goe2flag=0,clean=0,i=0;
/******************************************************************
    mainkey 处于键盘扫描标志
    numflag 变量序号
    goe2flag    进入变量修改标志
    clean   清屏标志,取消会闪屏
    i   记数变量
******************************************************************/
		u8 e2[32]={0}; 
		AT24CXX_Init();			//IIC初始
		AT24CXX_Read(0,e2,32);
    while(mainkey)
    {
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//选择变量,左键退出键盘扫面,右键锁定变量 
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
        /* * * * * * * * * * * * * * * * * * * * * * * * * * * */
        if(!Key_Scan(GPIOB,GPIO_Pin_11) )              //右移
        {
            Delay(10000);		
            
            while(!Key_Scan(GPIOB,GPIO_Pin_11))
            {
                
                goe2flag=1;
                clean=1; 
                
            }
        }
        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
        if(!Key_Scan(GPIOB,GPIO_Pin_10))              //上移
        {
            Delay(10000);		
            if(!Key_Scan(GPIOB,GPIO_Pin_10))
            {
                numflag=numflag<1?31:numflag-1; 
                clean=1;
            }
            while(!Key_Scan(GPIOB,GPIO_Pin_10));
        }
        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
        if(!Key_Scan(GPIOB,GPIO_Pin_0))              //左移
        {
           Delay(10000);		
            if(!Key_Scan(GPIOB,GPIO_Pin_0))
            {
                mainkey=0;
            }
            while(!Key_Scan(GPIOB,GPIO_Pin_0));
        }
        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
        if(!Key_Scan(GPIOB,GPIO_Pin_1))              //下移
        {
            Delay(10000);		
            if(!Key_Scan(GPIOB,GPIO_Pin_1))
            {
                numflag=numflag>30?0:numflag+1;
                clean=1;
            }
            while(!Key_Scan(GPIOB,GPIO_Pin_1));
        }
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//进入变量修改,左键确认当前修改,右键无功能 
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
        while(goe2flag)
        {
            if(!Key_Scan(GPIOB,GPIO_Pin_11))              //右移
            {
                Delay(10000);		
                if(!Key_Scan(GPIOB,GPIO_Pin_11))
                {
                    //没有功能
                }
                while(!Key_Scan(GPIOB,GPIO_Pin_11));
            }
            /* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
            if(!Key_Scan(GPIOB,GPIO_Pin_10))              //上移
            {
                Delay(10000);		
                if(!Key_Scan(GPIOB,GPIO_Pin_10))
                {
                    e2[numflag]=e2[numflag]>255?0:e2[numflag]+1;
                }
                while(!Key_Scan(GPIOB,GPIO_Pin_10));
            }
            /* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
            if(!Key_Scan(GPIOB,GPIO_Pin_0))              //退出
            {
                Delay(10000);		
                if(!Key_Scan(GPIOB,GPIO_Pin_0))
                {
                    goe2flag=0;
                    clean=1;
                }
                while(!Key_Scan(GPIOB,GPIO_Pin_0));
            }
            /* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
            if(!Key_Scan(GPIOB,GPIO_Pin_1))              //下移
            {
                Delay(10000);		
                if(!Key_Scan(GPIOB,GPIO_Pin_1))
                {
                    //e2[numflag]--;
                    e2[numflag]=e2[numflag]<0?255:e2[numflag]-1;
                }
                while(!Key_Scan(GPIOB,GPIO_Pin_1));
            } 
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
                //显示2 
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * */        
            if(clean==1)
            {
                   	OLED_clear();
                    clean=0;
            }
            
            LCD_P6x8Str(0,numflag%8,"*");
            for(i=0;i<8;i++)
            {
                LCD_P6x8Str(8,i,"EE(");
                LCD_P6x8n9999Num(26,i,numflag-(numflag%8)+i);
                LCD_P6x8Str(38,i,")");
                LCD_P6x8n9999Num(45,i,e2[numflag-(numflag%8)+i]);
            }            
            
        }
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
                //显示1 
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * */        
        if(clean==1)
        {
               OLED_clear();
                clean=0;
        }
        
        LCD_P6x8Str(0,numflag%8,">");
        
        for(i=0;i<8;i++)
        {
            LCD_P6x8Str(8,i,"EE(");
            LCD_P6x8n9999Num(26,i,numflag-(numflag%8)+i);
            LCD_P6x8Str(38,i,")");
            LCD_P6x8n9999Num(45,i,e2[numflag-(numflag%8)+i]);
        }
    }
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//给变量赋值
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * */     
//eg:
//servo.p=e2[2];
// SP=12,SD=10,SP1=28,SD1=120,SP2=24,SD2=90,MI=8,KI1=21;
//  MP=20,MD=12,MS=200,KP1=18,KD1=0;    
    
//    temperature.Hightemp = (float)(e2[0]);
//		temperature.Lowtemp = (float)(e2[1]);
//    temperature.Highhumi = (float)(e2[2]);
//		temperature.Lowhumi = (float)(e2[3]);
		 Hightemp = e2[0] ;
		 Lowtemp = e2[1];
		 Highhumi = e2[2] ;
		 Lowhumi = e2[3];		
		AT24CXX_Write(0,(u8*)e2,32);
		OLED_clear();  
}


