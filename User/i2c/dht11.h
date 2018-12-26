#ifndef __DHT11_H
#define __DHT11_H 
#include "sys.h"   
//检测外设时端口设置输入，控制外设设置输出 
#define DHT11_IO_IN()  {GPIOB->CRL&=0XFF0FFFFF;GPIOB->CRL|=8<<20;}//CRL(0-7口)设置为B5(移动4x5)
#define DHT11_IO_OUT() {GPIOB->CRL&=0XFF0FFFFF;GPIOB->CRL|=3<<20;}
////IO操作函数											   
#define	DHT11_DQ_OUT PBout(5) //数据端口	PA0 
#define	DHT11_DQ_IN  PBin(5)  //数据端口	PA0 


u8 DHT11_Init(void);//初始化DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//读取温湿度
u8 DHT11_Read_Byte(void);//读出一个字节
u8 DHT11_Read_Bit(void);//读出一个位
u8 DHT11_Check(void);//检测是否存在DHT11
void DHT11_Rst(void);//复位DHT11    
#endif















