#ifndef _SYSTICK_H_
#define _SYSTICK_H_
#include <stdint.h>

#define STK_ADD_BASE    0xE000E010

#define STK_CTRL        *(volatile uint32_t *)(STK_ADD_BASE + 0x00)
#define STK_LOAD        *(volatile uint32_t *)(STK_ADD_BASE + 0x04)
#define STK_VAL         *(volatile uint32_t *)(STK_ADD_BASE + 0x08)
#define STK_CALIB       *(volatile uint32_t *)(STK_ADD_BASE + 0x0C)

void STK_Disable();
void SysTick_Handler(void);

#endif
