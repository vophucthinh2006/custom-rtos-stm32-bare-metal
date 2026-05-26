#include <STK.h>

void STK_Disable(){
	STK_CTRL = 0x00000000;
	STK_LOAD = 0x00000000;
	STK_VAL = 0x00000000;
}
