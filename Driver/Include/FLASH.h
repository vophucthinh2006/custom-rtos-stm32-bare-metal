#ifndef __FLASH_H
#define __FLASH_H
#include <stdint.h>

#define FLASH_ACR        *(volatile uint32_t*)0x40022000
#define FLASH_KEYR       *(volatile uint32_t*)0x40022004
#define FLASH_OPTKEYR    *(volatile uint32_t*)0x40022008
#define FLASH_SR         *(volatile uint32_t*)0x4002200C
#define FLASH_CR         *(volatile uint32_t*)0x40022010
#define FLASH_AR         *(volatile uint32_t*)0x40022014
#define FLASH_OBR        *(volatile uint32_t*)0x4002201C
#define FLASH_WRPR       *(volatile uint32_t*)0x40022020
#define FLASH_KEYR2      *(volatile uint32_t*)0x40022044
#define FLASH_SR2        *(volatile uint32_t*)0x4002204C
#define FLASH_CR2        *(volatile uint32_t*)0x40022050
#define FLASH_AR2        *(volatile uint32_t*)0x40022054

typedef enum {
	FLASH_KEY_RDPRT      = 0x00A5,
	FLASH_KEY_1          = 0x45670123,
	FLASH_KEY_2          = 0xCDEF89AB
}FLASH_KEY_t;

typedef enum{
	FLASH_VERIFY_ERROR   = 0,
	FLASH_VERIFY_OK      =1
}FLASH_VERIFY_t;

extern volatile uint32_t FLASH_Page_Pointer;

void FLASH_Unlock();
uint8_t FLASH_Verify(uint32_t address, uint16_t data);
void FLASH_Program(uint32_t address, uint16_t data);
uint8_t FLASH_Erase_Page(uint32_t page);
void FLASH_Erase_Mass();
void FLASH_Program_Option(uint32_t address, uint16_t data);

#endif
