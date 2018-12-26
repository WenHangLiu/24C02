#ifndef __KEY_H__
#define __KEY_H__
#include "stm32f10x_it.h"
#include  "oled.h"
#include  "24c64.h"

/* * * * * 按键端口定义* * * * */
//#define key_U PTD2_IN
//#define key_D PTD4_IN
//#define key_L PTD0_IN
//#define key_R PTD6_IN

 /*******
 *按键按下标置
 KEY_ON 0
 KEY_OFF 1
 ********/
#define KEY_ON	0
#define KEY_OFF	1

/* * * * * 端口初始化* * * * */
 void key_gpioinit(void);

/* * * * * 键盘扫描 * * * */
//先读取E2PROM中的值,然后进入键盘扫描,确认退出键盘扫描后
//把值赋给变量,再把修改后的值写入E2PROM
 void key_scan(void);
u8 Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin);

#endif

