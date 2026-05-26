#include "FLASH.h"

volatile uint32_t FLASH_Page_Pointer;

void FLASH_Unlock(){
	if (FLASH_CR & (1 << 7)){
		FLASH_KEYR = FLASH_KEY_1;
		FLASH_KEYR = FLASH_KEY_2;
	}
}
uint8_t FLASH_Verify(uint32_t address, uint16_t data){
	uint16_t read_data = *(volatile uint16_t*)address;
	if (read_data == data) return FLASH_VERIFY_OK;
	else return FLASH_VERIFY_ERROR;
}
void FLASH_Program(uint32_t address, uint16_t data){
	FLASH_Unlock();
	while (FLASH_SR & (1 << 0));
	FLASH_CR |= (1 << 0);
	*(volatile uint16_t*)address = data;
	while (FLASH_SR & (1 << 0));
	FLASH_Verify(address, data);
	FLASH_CR &= ~(1 << 0);
}
uint8_t FLASH_Erase_Page(uint32_t page){
	FLASH_Unlock();
	while (FLASH_SR & (1 << 0));
	FLASH_CR |= (1 << 1);
	FLASH_AR = page;
	FLASH_CR |= (1 << 6);
	while (FLASH_SR & (1 << 0));
	for (uint16_t i = 0; i < 0x0400; i += 2 ){
		if (FLASH_Verify(page + i, 0xFFFF) != FLASH_VERIFY_OK) {
			FLASH_CR &= ~(1 << 1);
			return FLASH_VERIFY_ERROR;
			}
	}
	FLASH_CR &= ~(1 << 1);
	return FLASH_VERIFY_OK;
}
void FLASH_Erase_Mass(){
	FLASH_Unlock();
	while (FLASH_SR & (1 << 0));
	FLASH_CR |= (1 << 2);
	FLASH_CR |= (1 << 6);
	while (FLASH_SR & (1 << 0));
	//Check the erase operation by reading all the addresses in the user memory
	FLASH_CR &= ~(1 << 2);
}
void FLASH_Program_Option(uint32_t address, uint16_t data){
	FLASH_Unlock();
	while (FLASH_SR & (1 << 0));
	FLASH_CR |= (1 << 9);
	FLASH_CR |= (1 << 4);
	*(volatile uint16_t*)address = data;
	while (FLASH_SR & (1 << 0));
	//Read the programmed value and verify.
}
