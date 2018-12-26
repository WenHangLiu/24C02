#ifndef __KEY_H__
#define __KEY_H__
#include "stm32f10x_it.h"
#include  "oled.h"
#include  "24c64.h"

/* * * * * �����˿ڶ���* * * * */
//#define key_U PTD2_IN
//#define key_D PTD4_IN
//#define key_L PTD0_IN
//#define key_R PTD6_IN

 /*******
 *�������±���
 KEY_ON 0
 KEY_OFF 1
 ********/
#define KEY_ON	0
#define KEY_OFF	1

/* * * * * �˿ڳ�ʼ��* * * * */
 void key_gpioinit(void);

/* * * * * ����ɨ�� * * * */
//�ȶ�ȡE2PROM�е�ֵ,Ȼ��������ɨ��,ȷ���˳�����ɨ���
//��ֵ��������,�ٰ��޸ĺ��ֵд��E2PROM
 void key_scan(void);
u8 Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin);

#endif

