#ifndef __DHT11_H
#define __DHT11_H 
#include "sys.h"   
//�������ʱ�˿��������룬��������������� 
#define DHT11_IO_IN()  {GPIOB->CRL&=0XFF0FFFFF;GPIOB->CRL|=8<<20;}//CRL(0-7��)����ΪB5(�ƶ�4x5)
#define DHT11_IO_OUT() {GPIOB->CRL&=0XFF0FFFFF;GPIOB->CRL|=3<<20;}
////IO��������											   
#define	DHT11_DQ_OUT PBout(5) //���ݶ˿�	PA0 
#define	DHT11_DQ_IN  PBin(5)  //���ݶ˿�	PA0 


u8 DHT11_Init(void);//��ʼ��DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//��ȡ��ʪ��
u8 DHT11_Read_Byte(void);//����һ���ֽ�
u8 DHT11_Read_Bit(void);//����һ��λ
u8 DHT11_Check(void);//����Ƿ����DHT11
void DHT11_Rst(void);//��λDHT11    
#endif















