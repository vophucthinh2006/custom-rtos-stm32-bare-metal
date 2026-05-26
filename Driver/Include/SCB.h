#ifndef _SCB_H_
#define _SCB_H_
#include <stdint.h>

#define SCB_ADD_BASE    0xE000ED00

#define SCB_CPUID       *(volatile uint32_t*)(SCB_ADD_BASE + 0x00)
#define SCB_ICSR        *(volatile uint32_t*)(SCB_ADD_BASE + 0x04)
#define SCB_VTOR        *(volatile uint32_t*)(SCB_ADD_BASE + 0x08)
#define SCB_SHPR1       *(volatile uint32_t*)(SCB_ADD_BASE + 0x18)
#define SCB_SHPR2       *(volatile uint32_t*)(SCB_ADD_BASE + 0x1C)
#define SCB_SHPR3       *(volatile uint32_t*)(SCB_ADD_BASE + 0x20)
#define SCB_SHCSR       *(volatile uint32_t*)(SCB_ADD_BASE + 0x24)

#endif
