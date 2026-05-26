#include "USB.h"
void USB_Init(){
	NVIC_ISER0 |= (1 << 20);
}
void USB_IRQHandler(){

}
