#include<stm32f1xx.h>

void SysInit(){
	RCC->CR	|= (uint32_t)1<<0;
	while((RCC->CR & (uint32_t)(1<<1)) == 0);
	RCC->APB2ENR |= 1<<0;
	RCC->APB2ENR |= 1<<4;
}

void GpioInit(){
	GPIOC->CRH |= 3<<20;
	GPIOC->CRH |= 2<<20;
}

void Delay(int time){
	while(time--);
}
int main(void){
	SysInit();
	GpioInit();
	while(1){
		GPIOC->ODR |= 1<<13;
		Delay(100000);
		GPIOC->ODR &= ~(1<<13);
		Delay(100000);
	}
}
