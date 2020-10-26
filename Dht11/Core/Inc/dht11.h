/*
 * hdt11.h
 *
 *  Created on: Oct 26, 2020
 *      Author: phu_cuong
 */

#ifndef INC_DHT11_H_
#define INC_DHT11_H_
#include"stm32f1xx.h"
/*..........DHT11................................*/
void B5In(void);
void B5Out(void);
uint8_t DHT11_Init(void);
void DHT11_Rst(void);
uint8_t DHT11_Check(void);
uint8_t DHT11_Read_Bit(void);
uint8_t DHT11_Read_Byte(void);
uint8_t DHT11_Read_Data(uint8_t *temp,uint8_t *humi);
/*..........DHT11................................*/



#endif /* INC_DHT11_H_ */
