
#include "stm32f10x.h"
#include "stdlib.h"
#include "oled.h"
#include "oledfont.h"  
#include "string.h"
#include "stdarg.h"
#include "math.h"
#include "stdio.h"

//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   
#define bool _Bool
   
typedef unsigned char       uint8;  /*  8 bits */
typedef unsigned short int  uint16; /* 16 bits */
typedef unsigned long int   uint32; /* 32 bits */
typedef unsigned long long  uint64; /* 64 bits */

typedef char                int8;   /*  8 bits */
typedef short int           int16;  /* 16 bits */
typedef long  int           int32;  /* 32 bits */
typedef long  long          int64;  /* 64 bits */


typedef float	f32;
typedef double f64;


typedef volatile int8       vint8;  /*  8 bits */
typedef volatile int16      vint16; /* 16 bits */
typedef volatile int32      vint32; /* 32 bits */
typedef volatile int64      vint64; /* 64 bits */

typedef volatile uint8      vuint8;  /*  8 bits */
typedef volatile uint16     vuint16; /* 16 bits */
typedef volatile uint32     vuint32; /* 32 bits */
typedef volatile uint64     vuint64; /* 64 bits */

/**********************************************
----------------oled 延时函数----------------------
**********************************************/
static void oled_delay_ms(unsigned int t)
{
	int i;
	for( i=0;i<t;i++)
	{
		int a=42000;
		while(a--);
	}
}

static void oled_delay_us(unsigned int t)
{
	int i;
	for( i=0;i<t;i++)
	{
		int a=20;
		while(a--);
	}
}

/**********************************************
----------------- IIC Write command--------------
**********************************************/

void OLED_Write_Command(uint8_t data)
{
		uint8_t i,temp;
		temp=data;
		OLED_DC_RES();
		OLED_SCL_RES();
		oled_delay_us(1);
		for(i=0;i<8;i++)
			{
					if(temp & 0x80)			
								OLED_SDA_SET();
					else	OLED_SDA_RES();
					OLED_SCL_SET();
					oled_delay_us(1);
					OLED_SCL_RES();
					temp<<=1;
			}
}

/**********************************************
----------------- IIC Write data--------------
**********************************************/

void OLED_Write_Data(uint8_t data)
{
		uint8_t i,temp;
		temp=data;
		OLED_DC_SET();
		OLED_SCL_RES();
		oled_delay_us(1);
		for(i=0;i<8;i++)
			{
					if(temp & 0x80)			
								OLED_SDA_SET();
					else	OLED_SDA_RES();
					OLED_SCL_SET();
					oled_delay_us(1);
					OLED_SCL_RES();
					temp<<=1;
			}
}

void Pos_set(unsigned char x,unsigned char y)
{
		OLED_Write_Command(0xb0+y);
  	OLED_Write_Command(((x & 0xf0)>>4)|0x10);
  	OLED_Write_Command(  x & 0x0f); 
}

void OLED_clear(void)
{
		unsigned char y,x;
		for(y=0;y<8;y++)
			{
					OLED_Write_Command(0xb0+y);
					OLED_Write_Command(0x01);
					OLED_Write_Command(0x10);
					for(x=0;x<128;x++)
						OLED_Write_Data(0);
			}
}

/***************************************************************/
void SetStartColumn(unsigned char data)
{
	OLED_Write_Command(0x00+data%16);       // Set Lower Column Start Address for Page Addressing Mode
																					// Default => 0x00
	OLED_Write_Command(0x10+data/16);       // Set Higher Column Start Address for Page Addressing Mode
																					// Default => 0x10
}
/***************************************************************/

/***************************************************************/
void SetAddressingMode(unsigned char data)
{
	OLED_Write_Command(0x20);					// Set Memory Addressing Mode
	OLED_Write_Command(data);	  		  // Default => 0x02
																		// 0x00 => Horizontal Addressing Mode   水平
																		// 0x01 => Vertical Addressing Mode     垂直
																		// 0x02 => Page Addressing Mode        页
}
/***************************************************************/

/***************************************************************/
void SetColumnAddress(unsigned char a, unsigned char b)               	//列地址设置
{
	OLED_Write_Command(0x21);					// Set Column Address
	OLED_Write_Command(a);	    			// Default => 0x00 (Column Start Address)
	OLED_Write_Command(b);	    			// Default => 0x7F (Column End Address)
}
/***************************************************************/

/***************************************************************/
void SetPageAddress(unsigned char a, unsigned char b)										//页地址设置
{
	OLED_Write_Command(0x22);					//Set Page Address
	OLED_Write_Command(a);						//Default => 0x00 	(Page Start Address)
	OLED_Write_Command(b);	  			  //Default => 0x07 (Page End Address)
}
/***************************************************************/

/***************************************************************/
void SetStartLine(unsigned char d)
{
	OLED_Write_Command(0x40|d);				// Set Display Start Line
																		// Default => 0x40 (0x00)
}
/***************************************************************/

/***************************************************************/
void SetContrastControl(unsigned char d)
{
	OLED_Write_Command(0x81);					//Set Contrast Control
	OLED_Write_Command(d);						//Default => 0x7F
}
/***************************************************************/

/***************************************************************/
void Set_Charge_Pump(unsigned char d)
{
	OLED_Write_Command(0x8D);					//Set Charge Pump
	OLED_Write_Command(0x10|d);				//Default => 0x10
																		//0x10 (0x00) => Disable Charge Pump
																		//0x14 (0x04) => Enable Charge Pump
}
/***************************************************************/

/***************************************************************/
void Set_Segment_Remap(unsigned char d)
{
	OLED_Write_Command(0xA0|d);  			//Set Segment Re-Map
																		//Default => 0xA0
																		//0xA0 (0x00) => Column Address 0 Mapped to SEG0
																		//0xA1 (0x01) => Column Address 0 Mapped to SEG127
}
/***************************************************************/

/***************************************************************/
void Set_Entire_Display(unsigned char d)
{
	OLED_Write_Command(0xA4|d);  			//Set Entire Display On / Off
																		//Default => 0xA4
																		//0xA4 (0x00) => Normal Display
																		//0xA5 (0x01) => Entire Display On
}
/***************************************************************/

/***************************************************************/
void Set_Inverse_Display(unsigned char d)
{
	OLED_Write_Command(0xA6|d); 			//Set Inverse Display On/Off
																		//Default => 0xA6
																		//0xA6 (0x00) => Normal Display
																		//0xA7 (0x01) => Inverse Display On
}
/***************************************************************/

/***************************************************************/
void Set_Multiplex_Ratio(unsigned char d)
{
	OLED_Write_Command(0xA8);						//Set Multiplex Ratio
	OLED_Write_Command(d);	 				   //Default => 0x3F (1/64 Duty)
}
/***************************************************************/

/***************************************************************/
void Set_Display_On_Off(unsigned char d)
{
	OLED_Write_Command(0xAE|d);  			//Set Display On/Off
																		//Default => 0xAE
																		//0xAE (0x00) => Display Off
																		//0xAF (0x01) => Display On
}
/***************************************************************/

/***************************************************************/
void SetStartPage(unsigned char d)
{
	OLED_Write_Command(0xB0|d);				//Set Page Start Address for Page Addressing Mode
																		//Default => 0xB0 (0x00)
}
/***************************************************************/

/***************************************************************/
void Set_Common_Remap(unsigned char d)
{
	OLED_Write_Command(0xC0|d);				//Set COM Output Scan Direction
																		//Default => 0xC0
																		//0xC0 (0x00) => Scan from COM0 to 63
																		//0xC8 (0x08) => Scan from COM63 to 0
}
/***************************************************************/

/***************************************************************/
void Set_Display_Offset(unsigned char d)
{
	OLED_Write_Command(0xD3);  			  //Set Display Offset
	OLED_Write_Command(d);	  			  //Default => 0x00
}
/***************************************************************/

/***************************************************************/
void Set_Display_Clock(unsigned char d)
{
	OLED_Write_Command(0xD5);					//Set Display Clock Divide Ratio / Oscillator Frequency
	OLED_Write_Command(d);	  				 //Default => 0x80
																		//D[3:0] => Display Clock Divider
																		//D[7:4] => Oscillator Frequency
}	
/***************************************************************/

/***************************************************************/
void Set_Precharge_Period(unsigned char d)
{
	OLED_Write_Command(0xD9);				//Set Pre-Charge Period
	OLED_Write_Command(d);					//Default => 0x22 (2 Display Clocks [Phase 2] / 2 Display Clocks [Phase 1])
																	//D[3:0] => Phase 1 Period in 1~15 Display Clocks
																		//D[7:4] => Phase 2 Period in 1~15 Display Clocks
}
/***************************************************************/

/***************************************************************/
void Set_Common_Config(unsigned char d)
{
	OLED_Write_Command(0xDA);				//Set COM Pins Hardware Configuration
	OLED_Write_Command(0x02|d);			//Default => 0x12 (0x10)
																	//Alternative COM Pin Configuration
																	//Disable COM Left/Right Re-Map
}
/***************************************************************/

/***************************************************************/
void Set_VCOMH(unsigned char d)
{
	OLED_Write_Command(0xDB);				//Set VCOMH Deselect Level
	OLED_Write_Command(d);	   		 //Default => 0x20 (0.77*VCC)
}
/***************************************************************/

/***************************************************************/
void Set_NOP(void)
{
	OLED_Write_Command(0xE3);				// Command for No Operation
}
/***************************************************************/


void LCD_P8x16Str(unsigned char x,unsigned char y,char ch[])
{
    char c=0,i=0,j=0;
    while (ch[j]!='\0')
     {
			 
				c =ch[j]-32;
			 if(ch[j]=='\r')
				 x+=16;
			 else if(ch[j]=='\n')
				{x=0;y+=2;} 
       if(x>120)
				 {
						x=0;
						y+=2;
				 }
			 
			 if(ch[j]>=32)
			 { 
				 Pos_set(x,y);  
				 
				 for(i=0;i<8;i++)     
					OLED_Write_Data(F8X16[c*16+i]);
				 
				 Pos_set(x,y+1);    
				 for(i=0;i<8;i++)     
					OLED_Write_Data(F8X16[c*16+i+8]);  
				 x+=8; 	   
			 }
			 j++;
     }
}

void LCD_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[])
{
  unsigned char c=0,i=0,j=0;      
  while (ch[j]!='\0')
  {    
    c =ch[j]-32;
    if(x>126){x=0;y++;}
    Pos_set(x,y);    
  	for(i=0;i<6;i++)     
  	  OLED_Write_Data(F6x8[c][i]);  
  	x+=6;
  	j++;
  }
}

//==============================================================
//???:LCD_P6x8f2_3Num(unsigned char x,unsigned char y,float num)
//????:??99.99小数点后2位
//??:?????(x,y),y????0~7,??????
//??:?
//==============================================================  
void LCD_P6x8f2_2Num(unsigned char x,unsigned char y,float num)
{
  unsigned char i=0,j=0,k=0;   
  float ff;
  int8 n[4];
  if(num<0)
  {
    if(x>126){x=0;y++;}
    Pos_set(x,y);  
    for(i=0;i<6;i++)
			OLED_Write_Data(F6x8[13][i]);		
    x+=6;
    ff=-num;
  }
  else ff=num;
  n[1] = (int8)ff;
  
  n[0] = n[1] / 10 % 10;
  n[1] = n[1] % 10;
  
  n[2]= (int16)(ff*10)%10;
  n[3]= (int16)(ff*100)%10;
  for(k=0;k<5;k++)
  {  
    if(x>126){x=0;y++;}
    
    Pos_set(x,y);   
    if(k==2)
    {
      for(i=0;i<6;i++)     
			OLED_Write_Data(F6x8[14][i]);	 
        x+=6;
    }
    else
    {
      if(!(j==0&&n[j]==0))
      {
  	for(i=0;i<6;i++) 
			OLED_Write_Data(F6x8[n[j]+16][i]);					 
  	x+=6;
      }
      j++;
    }
  }
}
void Draw_NchuLogo(void)
{ 	
  unsigned int ii=0;
  unsigned char x,y;       
  
	for(y=0;y<8;y++)
	{
		Pos_set(34,y);				
    for(x=34;x<94;x++)
	    {      
	    	OLED_Write_Data(NchuLOGO60x64[ii++]);	    	
	    }
	}
}
//==============================================================
//???:LCD_P6x8Str(unsigned char x,unsigned char y,unsigned char *p)
//????:??-9999~9999?????
//??:?????(x,y),y????0~7,??????
//??:?
//==============================================================  
void LCD_P6x8n9999Num(unsigned char x,unsigned char y,int16 num)
{
  unsigned char i=0,k=0;   
  uint16 ff;
  int8 n[4];
    if(num<0)
  {
    if(x>126){x=0;y++;}
    Pos_set(x,y);   
    for(i=0;i<6;i++)     
			OLED_Write_Data(F6x8[13][i]);	
    x+=6;
    ff=-num;
  }
  else ff = num;
  n[0] = ff / 1000 % 10;
  n[1] = ff / 100 % 10;
  n[2]= ff / 10 % 10;
  n[3]= ff % 10;
  for(k=0;k<4;k++)
  {  
    if(x>126){x=0;y++;}
    Pos_set(x,y);  
      if(n[k]!=0||k==3)
      {
  	for(i=0;i<6;i++)
			OLED_Write_Data(F6x8[n[k]+16][i]);					 
  	x+=6;
      }
  }
}


//显示汉字

void LCD_P16x16Str(unsigned char x,unsigned char y,unsigned char ch[])
{
	unsigned char wm=0,ii = 0,j;
        while(ch[ii] != '\0')
        {
         if(ch[ii]==Cword[wm].word[0])
         {
           if(x>112){x=0;y+=2;}
           if(y>6){x=0;y=0;OLED_clear();}
           if(ch[ii+1]==Cword[wm].word[1])
           {
            Pos_set(x , y);
             for(j = 0;j < 16;j++)               
              {
                 OLED_Write_Data(Cword[wm].code[j]);	
              }      
             Pos_set(x,y + 1); 
             for(j = 0;j < 16;j++)          
              {
               OLED_Write_Data(Cword[wm].code[j+16]); 		
              }
             
             ii+=2;
             wm=0;
             x+=16;
           }
           else wm+=1;
         }
         else wm+=1;
        }
}
//显示汉字
void OLED_Print(unsigned char x, unsigned char y, char ch[])
{
	unsigned char ch2[3];
	unsigned char ii=0;        
	while(ch[ii] != '\0')
	{
		if(ch[ii] > 127)
		{
			ch2[0] = ch[ii];
	 		ch2[1] = ch[ii + 1];
			ch2[2] = '\0';			//汉字2个字节
                        if(x>112){x=0;y+=2;}
                        if(y>6){x=0;y=0;OLED_clear();}
			LCD_P16x16Str(x , y, ch2);	//显示汉字
			x += 16;
			ii += 2;
}
}
	}
	
void LCD_PrintU16(unsigned char x,unsigned char y,unsigned int num)
{
	unsigned char tmp[6],i;
	tmp[5]=0;
	tmp[4]=(unsigned char)(num%10+0x30);
	tmp[3]=(unsigned char)(num/10%10+0x30);
	tmp[2]=(unsigned char)(num/100%10+0x30);
	tmp[1]=(unsigned char)(num/1000%10+0x30);
	tmp[0]=(unsigned char)(num/10000%10+0x30);
	
	for(i=0;i<4;i++)
	{
		if(tmp[i]=='0')
			tmp[i]=' ';
		else
			break;
	}
	
	LCD_P6x8Str(x,y,tmp);
	
}	
	
	
void OLED_Printf(unsigned char x,unsigned char y,const char *fmt,...)
{
	static unsigned char last_len[4]={0,0,0,0};	
	static char LCD_BUF[128]={0}; 
	unsigned char len;
	unsigned char i;
	__va_list ap;
	
	va_start(ap,fmt);
	vsprintf((char *)LCD_BUF,fmt,ap);
	va_end(ap);
	
	len=strlen((char *)LCD_BUF)+2*y;
	for(i=len;i<last_len[x];i++)
	{
		LCD_BUF[i-2*y]=' ';
	}
	LCD_BUF[i-2*y]=0;
	LCD_P8x16Str(x,y,LCD_BUF);
	last_len[x]=len;
}


void OLED_Configuration(void)        
{
	/*-------------------------------------GPIO初始化-----------------*/
		GPIO_InitTypeDef	GPIO_InitStructure;                          //GPIO结构体声明
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		OLED_SCL_SET();
		OLED_RST_RES();
		oled_delay_ms(200);
		OLED_RST_SET();

    Set_Display_On_Off(0x00);		// Display Off (0x00/0x01)
    Set_Display_Clock(0x80);		// Set Clock as 100 Frames/Sec
    Set_Multiplex_Ratio(0x3F);		// 1/64 Duty (0x0F~0x3F)
    Set_Display_Offset(0x00);		// Shift Mapping RAM Counter (0x00~0x3F)
    SetStartLine(0x00);			    // Set Mapping RAM Display Start Line (0x00~0x3F)
    Set_Charge_Pump(0x04);		    // Enable Embedded DC/DC Converter (0x00/0x04)
    SetAddressingMode(0x02);		// Set Page Addressing Mode (0x00/0x01/0x02)
    Set_Segment_Remap(0x01);		// Set SEG/Column Mapping     
    Set_Common_Remap(0x08);			// Set COM/Row Scan Direction 
    Set_Common_Config(0x10);		// Set Sequential Configuration (0x00/0x10)
    SetContrastControl(0xCF);	    // Set SEG Output Current
    Set_Precharge_Period(0xF1);		// Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    Set_VCOMH(0x40);			    // Set VCOM Deselect Level
    Set_Entire_Display(0x00);		// Disable Entire Display On (0x00/0x01)
    Set_Inverse_Display(0x00);		// Disable Inverse Display On (0x00/0x01)  
    Set_Display_On_Off(0x01);		// Display On (0x00/0x01)
    OLED_clear();
		Pos_set(0,0);
		
}









