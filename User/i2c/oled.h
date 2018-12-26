

#ifndef _oled_H_
#define _oled_H_
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
//#define OLED_SCL_RES() GPIO_ResetBits(GPIOB,GPIO_Pin_9)  //SCL---D0
//#define OLED_SCL_SET() GPIO_SetBits(GPIOB,GPIO_Pin_9)

//#define OLED_SDA_RES() GPIO_ResetBits(GPIOB,GPIO_Pin_7)  //SDA----D1
//#define OLED_SDA_SET() GPIO_SetBits(GPIOB,GPIO_Pin_7)

//#define OLED_RST_RES() GPIO_ResetBits(GPIOB,GPIO_Pin_5)  //RST
//#define OLED_RST_SET() GPIO_SetBits(GPIOB,GPIO_Pin_5)

//#define OLED_DC_RES() GPIO_ResetBits(GPIOB,GPIO_Pin_6)  //DC
//#define OLED_DC_SET() GPIO_SetBits(GPIOB,GPIO_Pin_6)
#define OLED_SCL_RES() GPIO_ResetBits(GPIOB,GPIO_Pin_12)  //SCL---D0·
#define OLED_SCL_SET() GPIO_SetBits(GPIOB,GPIO_Pin_12)

#define OLED_SDA_RES() GPIO_ResetBits(GPIOB,GPIO_Pin_13)  //SDA----D1
#define OLED_SDA_SET() GPIO_SetBits(GPIOB,GPIO_Pin_13)

#define OLED_RST_RES() GPIO_ResetBits(GPIOB,GPIO_Pin_14)  //RST
#define OLED_RST_SET() GPIO_SetBits(GPIOB,GPIO_Pin_14)

#define OLED_DC_RES() GPIO_ResetBits(GPIOB,GPIO_Pin_15)  //DC
#define OLED_DC_SET() GPIO_SetBits(GPIOB,GPIO_Pin_15)

void OLED_Configuration(void);
void Draw_NchuLogo(void);
void OLED_Print(unsigned char x, unsigned char y, char ch[]);//中文
void OLED_Printf(unsigned char x,unsigned char y,const char *fmt,...);//OLED_Printf(0,2,"%d",xx);打印数据
void LCD_P8x16Str(unsigned char x,unsigned char y,char ch[]);//LCD_P8x16Str(0,0,"Failed");	LCD_P8x16Str(0,6,"1");
void OLED_clear(void);
extern void Draw_NchuLogo(void); 
extern void LCD_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[]);  
extern void LCD_P6x8f2_2Num(unsigned char x,unsigned char y,float num);  
extern void LCD_P6x8n9999Num(unsigned char x,unsigned char y,int16 num); 
extern void LCD_PrintU16(unsigned char x,unsigned char y,unsigned int num);
#endif 


