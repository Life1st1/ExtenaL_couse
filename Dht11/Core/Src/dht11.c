/*
 * dht11.c
 *
 *  Created on: Oct 26, 2020
 *      Author: phu_cuong
 */
#include"dht11.h"
#include"delay.h"
/*..........DHT11................................*/
void B5In(void){
	GPIOB->CRL &= 0xFF0FFFFF;
	GPIOB->CRL|=8<<20;
}
/*..........DHT11................................*/
void B5Out(void){
	GPIOB->CRL &= 0xFF0FFFFF;
	GPIOB->CRL|=3<<20;
}
/*..........DHT11................................*/
uint8_t DHT11_Init(void){
	B5Out();
	GPIOB->ODR |=(1<<5);
	DHT11_Rst();
	return DHT11_Check();
}
/*..........DHT11................................*/
void DHT11_Rst(void){
	B5Out();
	GPIOB->ODR &= ~(1<<5);
	delay_ms(20);
	GPIOB->ODR |=(1<<5);
	delay_us(30);
}
/*..........DHT11................................*/
uint8_t DHT11_Check(void){
	uint8_t time=0;
	B5In();
	while(((GPIOB->IDR & (uint32_t)(1<<5))!=0)&&time<100){time++;delay_us(1);}//cho xuong
	if(time>=100)
	return 1;//loi
	else time=0;
	while(((GPIOB->IDR & (uint32_t)(1<<5))==0)&&time<100){time++;delay_us(1);}// cho len
	if(time>=100)
	return 1;//loi
	else return 0;
}
/*..........DHT11................................*/
uint8_t DHT11_Read_Bit(void){
	uint8_t time=0;

	while(((GPIOB->IDR & (uint32_t)(1<<5))!=0)&&time<100){time++;delay_us(1);}//cho xuong

	time=0;
	while(((GPIOB->IDR & (uint32_t)(1<<5))==0)&&time<100){time++;delay_us(1);}// cho len
	delay_us(40);
	if(((GPIOB->IDR & (uint32_t)(1<<5))!=0)) return 1;
	else return 0;
}
/*..........DHT11................................*/
uint8_t DHT11_Read_Byte(void){
	uint8_t i=0;
	uint8_t data=0;//00000001

	for(i=0;i<8;i++){

		data<<=1;
		data|=DHT11_Read_Bit();

	}
	return data;
}
/*..........DHT11................................*/
uint8_t DHT11_Read_Data(uint8_t *temp,uint8_t *humi){
	uint8_t i=0;
	uint8_t buf[5];

	DHT11_Rst();

	if(DHT11_Check()==0)
	{
		for(i=0;i<5;i++){

			buf[i]=DHT11_Read_Byte();

		}

		if(buf[0]+buf[1]+buf[2]+buf[3]==buf[4])
		{
			*humi=buf[0];
			*temp=buf[2];
		}
	}else return 1;//loi
	return 0;//ok
}
/*..........DHT11................................*/




