#include "EXTI.h"

void EXTI_Init(
		EXTI_PORT_t port,
		uint8_t pin,
		EXTI_MODE_t mode
		){
	if (pin > 15){
		return;
	}

	volatile uint32_t *EXTI_;


	if (pin < 4){
		EXTI_ = &AFIO_EXTICR1;
	}
	else if ((pin >=4) && (pin < 8)){
		EXTI_ = &AFIO_EXTICR2;
	}
	else if ((pin <= 8) && (pin < 12)){
		EXTI_ = &AFIO_EXTICR3;
	}
	else if ((pin <= 12) && (pin <16)){
		EXTI_ = &AFIO_EXTICR4;
	}

	*EXTI_ &= ~(0b1111 << ((pin % 4) * 4));
	*EXTI_ |= (port << ((pin % 4) * 4));

	EXTI_IMR |= (1 << pin);

	switch(mode){
	case EXTI_MODE_RISING:
		EXTI_RTSR &= ~(1 << pin);
		EXTI_FTSR &= ~(1 << pin);
		EXTI_RTSR |= (1 << pin);
		break;
	case EXTI_MODE_FALLING:
		EXTI_RTSR &= ~(1 << pin);
		EXTI_FTSR &= ~(1 << pin);
		EXTI_FTSR |= (1 << pin);
		break;
	case EXTI_MODE_BOTH:
		EXTI_RTSR &= ~(1 << pin);
		EXTI_FTSR &= ~(1 << pin);
		EXTI_RTSR |= (1 << pin);
		EXTI_FTSR |= (1 << pin);
		break;
	default: return;
	}

	if (pin <= 4){
		NVIC_ISER0 |= (1 << (6 + pin));
	}
	else if ((5 >= pin) && (pin <= 9)){
		NVIC_ISER0 |= (1 << 23);
	}
	else if ((10 >= pin) && (pin <= 15)){
		NVIC_ISER1 |= (1 << (40 - 32));
	}
}

void EXTI0_IRQHandler(void){
	if (EXTI_PR & (1 << 0)){
		//do something
		for (int i = 0; i <= 100000; i++);
		if (GPIO_Read_Pin(GPIO_PORTB, 0) == 1){
			GPIO_Write_Pin(GPIO_PORTB, 1, GPIO_PIN_SET);
		}
		else {
			GPIO_Write_Pin(GPIO_PORTB, 1, GPIO_PIN_RESET);
		}
		EXTI_PR |= (1 << 0);
	}
}
void EXTI5_9_IRQHandler(void){
	for (uint8_t pin = 5; pin <= 9; pin++){
		if (EXTI_PR & (1 << pin)){
			//do something
			EXTI_PR |= (1 << pin);
		}
	}
}
void EXTI10_15_IRQHandler(void){
	for (uint8_t pin = 10; pin <= 15; pin++){
		if (EXTI_PR & (1 << pin)){
			//do something
			EXTI_PR |= (1 << pin);
		}
	}
}
void NVIC_UART_Enable(
		EXTI_UART_t UART_
		){
	switch (UART_){
	case EXTI_UART1: NVIC_ISER1 |= (1 << (37 - 32)); break;
	case EXTI_UART2: NVIC_ISER1 |= (1 << (45 - 32)); break;
	case EXTI_UART3: NVIC_ISER1 |= (1 << (46 - 32)); break;
	default: return;
	}
}
void _Interrupts_Disable(void){
	__asm volatile ("cpsid i");
}
void _Interrupts_Enable(void){
	__asm volatile ("cpsie i");
}
void _Set_MSP(uint32_t TopOfMainStack){
	__asm volatile ("MSR msp, %0" : : "r" (TopOfMainStack) : );
}
void NVIC_Disable(){
	NVIC_ICER0 = 0xFFFFFFFF;
	NVIC_ICER1 = 0xFFFFFFFF;
	NVIC_ICPR0 = 0xFFFFFFFF;
	NVIC_ICPR1 = 0xFFFFFFFF;
}
