#ifndef __EXTI_H
#define __EXTI_H
#include <stdint.h>
#include "AFIO.h"
#include "UART.h"

#define EXTI_ADD_BASE    0x40010400UL
#define NVIC_ADD_BASE    0xE000E100UL

#define EXTI_IMR         (*(volatile uint32_t*)(EXTI_ADD_BASE + 0x00))
#define EXTI_EMR         (*(volatile uint32_t*)(EXTI_ADD_BASE + 0x04))
#define EXTI_RTSR        (*(volatile uint32_t*)(EXTI_ADD_BASE + 0x08))
#define EXTI_FTSR        (*(volatile uint32_t*)(EXTI_ADD_BASE + 0x0C))
#define EXTI_SWIER       (*(volatile uint32_t*)(EXTI_ADD_BASE + 0x10))
#define EXTI_PR          (*(volatile uint32_t*)(EXTI_ADD_BASE + 0x14))

#define NVIC_ISER0       (*(volatile uint32_t*)(NVIC_ADD_BASE + 0x000))
#define NVIC_ISER1       (*(volatile uint32_t*)(NVIC_ADD_BASE + 0x004))
#define NVIC_ISER2       (*(volatile uint32_t*)(NVIC_ADD_BASE + 0x008))
#define NVIC_ICER0       (*(volatile uint32_t*)(NVIC_ADD_BASE + 0x080))
#define NVIC_ICER1       (*(volatile uint32_t*)(NVIC_ADD_BASE + 0x084))
#define NVIC_ICER2       (*(volatile uint32_t*)(NVIC_ADD_BASE + 0x088))
#define NVIC_ISPR0       (*(volatile uint32_t*)(NVIC_ADD_BASE + 0x100))
#define NVIC_ISPR1       (*(volatile uint32_t*)(NVIC_ADD_BASE + 0x104))
#define NVIC_ISPR2       (*(volatile uint32_t*)(NVIC_ADD_BASE + 0x108))
#define NVIC_ICPR0       (*(volatile uint32_t*)(NVIC_ADD_BASE + 0x180))
#define NVIC_ICPR1       (*(volatile uint32_t*)(NVIC_ADD_BASE + 0x184))
#define NVIC_ICPR2       (*(volatile uint32_t*)(NVIC_ADD_BASE + 0x188))
#define NVIC_IABR0       (*(volatile uint32_t*)(NVIC_ADD_BASE + 0x200))
#define NVIC_IABR1       (*(volatile uint32_t*)(NVIC_ADD_BASE + 0x204))
#define NVIC_IABR2       (*(volatile uint32_t*)(NVIC_ADD_BASE + 0x208))
#define NVIC_IPR0        (*(volatile uint32_t*)(NVIC_ADD_BASE + 0x300))
// TO NCIC_IPR20
#define NVIC_STIR        (*(volatile uint32_t*)(NVIC_ADD_BASE + 0xE00))

//PORT
typedef enum{
	EXTI_PORTA = 0b0000,
	EXTI_PORTB = 0b0001,
	EXTI_PORTC = 0b0010
}EXTI_PORT_t;

typedef enum{
	EXTI_MODE_RISING,
	EXTI_MODE_FALLING,
	EXTI_MODE_BOTH
}EXTI_MODE_t;

//UART
typedef enum{
	EXTI_UART1,
	EXTI_UART2,
	EXTI_UART3
}EXTI_UART_t;

void EXTI_Init(
		EXTI_PORT_t port,
		uint8_t pin,
		EXTI_MODE_t mode
		);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI5_9_IRQHandler(void);
void EXTI10_15_IRQHandler(void);
void _Interrupts_Disable(void);
void _Interrupts_Enable(void);
void _Set_MSP(uint32_t TopOfMainStack);

void NVIC_UART_Enable(
		EXTI_UART_t UART_
		);
void NVIC_Disable();

#endif
