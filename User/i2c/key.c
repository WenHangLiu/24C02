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

/* * * * * �˿ڳ�ʼ��* * * * */
void key_gpioinit()
{

  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_10|GPIO_Pin_1|GPIO_Pin_0; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 

	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_SetBits(GPIOB, GPIO_Pin_11|GPIO_Pin_10|GPIO_Pin_1|GPIO_Pin_0);	//ѡ �� �� ��
        
}

 u8 Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{			
		/*����Ƿ��а������� */
   	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON ) 
	  {	   
	 	 /*��ʱ����*/
	  	Delay(10000);		
	   		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
					{	 
						/*�ȴ������ͷ� */
						while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_OFF);   
			 			return 	KEY_ON;	 
					}
			else
					return KEY_OFF;
		}
	else
		return KEY_OFF;
}
/* * * * * ����ɨ�� * * * */
//�ȶ�ȡE2PROM�е�ֵ,Ȼ��������ɨ��,ȷ���˳�����ɨ���
//��ֵ��������,�ٰ��޸ĺ��ֵд��E2PROM
void key_scan()
{
	
    u8 mainkey=1,numflag=0,goe2flag=0,clean=0,i=0;
/******************************************************************
    mainkey ���ڼ���ɨ���־
    numflag �������
    goe2flag    ��������޸ı�־
    clean   ������־,ȡ��������
    i   ��������
******************************************************************/
		u8 e2[32]={0}; 
		AT24CXX_Init();			//IIC��ʼ
		AT24CXX_Read(0,e2,32);
    while(mainkey)
    {
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//ѡ�����,����˳�����ɨ��,�Ҽ��������� 
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
        /* * * * * * * * * * * * * * * * * * * * * * * * * * * */
        if(!Key_Scan(GPIOB,GPIO_Pin_11) )              //����
        {
            Delay(10000);		
            
            while(!Key_Scan(GPIOB,GPIO_Pin_11))
            {
                
                goe2flag=1;
                clean=1; 
                
            }
        }
        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
        if(!Key_Scan(GPIOB,GPIO_Pin_10))              //����
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
        if(!Key_Scan(GPIOB,GPIO_Pin_0))              //����
        {
           Delay(10000);		
            if(!Key_Scan(GPIOB,GPIO_Pin_0))
            {
                mainkey=0;
            }
            while(!Key_Scan(GPIOB,GPIO_Pin_0));
        }
        /* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
        if(!Key_Scan(GPIOB,GPIO_Pin_1))              //����
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
//��������޸�,���ȷ�ϵ�ǰ�޸�,�Ҽ��޹��� 
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
        while(goe2flag)
        {
            if(!Key_Scan(GPIOB,GPIO_Pin_11))              //����
            {
                Delay(10000);		
                if(!Key_Scan(GPIOB,GPIO_Pin_11))
                {
                    //û�й���
                }
                while(!Key_Scan(GPIOB,GPIO_Pin_11));
            }
            /* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
            if(!Key_Scan(GPIOB,GPIO_Pin_10))              //����
            {
                Delay(10000);		
                if(!Key_Scan(GPIOB,GPIO_Pin_10))
                {
                    e2[numflag]=e2[numflag]>255?0:e2[numflag]+1;
                }
                while(!Key_Scan(GPIOB,GPIO_Pin_10));
            }
            /* * * * * * * * * * * * * * * * * * * * * * * * * * * * */
            if(!Key_Scan(GPIOB,GPIO_Pin_0))              //�˳�
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
            if(!Key_Scan(GPIOB,GPIO_Pin_1))              //����
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
                //��ʾ2 
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
                //��ʾ1 
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
//��������ֵ
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


