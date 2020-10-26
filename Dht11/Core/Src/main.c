#include"dht11.h"
#include"stdio.h"
#include<string.h>
#define msg "\n"
void SysInit(void){
	RCC->CR |= 1<<0; 		// HSI on
	//while((RCC->CR & (uint32_t)(1>>1)) == 0);
	RCC->APB2ENR |= (uint32_t)(1<<0);
	RCC->APB2ENR |= (uint32_t)(1<<4);
	RCC->APB2ENR |= (uint32_t)(1<<3);
	RCC->APB2ENR |= (uint32_t)(1<<2);
	RCC->APB2ENR |= (uint32_t)(1<<14);  // Uart1 Enable
}

void GpioInit(void){
	GPIOC->CRH &= 0xFF0FFFFF;
	//GPIOB->CRL &= 0xFF0FFFFF;
	GPIOA->CRL &= 0xFFFFFF0F;
	GPIOC->CRH |= (uint32_t)(3<<20);
	GPIOC->CRH |= (uint32_t)(1<<22);
	//GPIOB->CRL |= (uint32_t)(3<<20);
	//GPIOB->CRL |= (uint32_t)(1<<22);
	GPIOA->CRH |= (uint32_t)(3<<4);			// Mode Max 50 Hz
	GPIOA->CRH |= (uint32_t)(2<<6);			// alternate function push full
	//GPIOA->CRH |= (uint32_t)(3<<4;
	//GPIOA->CRH |= (uint32_t)(1<<6;
}

void UartInit(void){
	USART1->CR1 |= (uint32_t)(3<<2); 		//Tx Rx Enable
	USART1->CR1 |= (uint32_t)(1<<13);		//USART1 Enable
	USART1->BRR |= (uint32_t)(4<<4);
	USART1->BRR |= (uint32_t)(5<<0);
}

void UartTx(uint8_t* data, uint8_t size){
	uint8_t i;
	for(i=0;i < size;i++){
		USART1->DR = *(data+i);
		while((USART1->SR & (uint32_t)(1<<6))==0);
	}
}


int main(void){
	uint8_t humi=0;
	uint8_t temp=0;
	char chuoi1[3];
	char chuoi2[3];
	//uint8_t a = 23;
	SysInit();
	GpioInit();
	UartInit();
	delay_init(8);
	DHT11_Init();
	while(1){
		UartTx((uint8_t*)msg, sizeof(msg));
		DHT11_Read_Data(&temp, &humi);
		itoa(humi,chuoi1,10);
		itoa(temp,chuoi2,10);
		GPIOC->ODR |= 1<<13;
		delay_ms(1000);
		GPIOC->ODR &= ~(1<<13);
		delay_ms(100);
		UartTx(&chuoi1, sizeof(chuoi1));
		delay_ms(100);
		UartTx((uint8_t*)"-",1);
		UartTx(&chuoi2, sizeof(chuoi2));
		delay_ms(100);
	}
	return 0;
}
