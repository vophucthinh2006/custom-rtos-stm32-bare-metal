#ifndef __USB_H
#define __USB_H
#include <stdint.h>
#include "EXTI.h"

#define USB_ADD_BASE    0x40005C00


#define USB_EPOR        *(volatile uint16_t*)(USB_ADD_BASE + 0x00)
#define USB_EP1R        *(volatile uint16_t*)(USB_ADD_BASE + 0x04)
#define USB_EP2R        *(volatile uint16_t*)(USB_ADD_BASE + 0x08)
#define USB_EP3R        *(volatile uint16_t*)(USB_ADD_BASE + 0x0C)
#define USB_EP4R        *(volatile uint16_t*)(USB_ADD_BASE + 0x10)
#define USB_EO5R        *(volatile uint16_t*)(USB_ADD_BASE + 0x14)
#define USB_EP6R        *(volatile uint16_t*)(USB_ADD_BASE + 0x18)
#define USB_EP7R        *(volatile uint16_t*)(USB_ADD_BASE + 0x1C)
#define USB_CNTR        *(volatile uint16_t*)(USB_ADD_BASE + 0x40)
#define USB_ISTR        *(volatile uint16_t*)(USB_ADD_BASE + 0x44)
#define USB_FNR         *(volatile uint16_t*)(USB_ADD_BASE + 0x48)
#define USB_DADDR       *(volatile uint8_t*)(USB_ADD_BASE + 0x4C)
#define USB_BTABLE      *(volatile uint16_t*)(USB_ADD_BASE + 0x50)

void USB_Init();
void USB_IRQHandler();

#endif
