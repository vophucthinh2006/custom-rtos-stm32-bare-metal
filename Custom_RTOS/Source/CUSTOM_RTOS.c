#include <CUSTOM_RTOS.h>

uint32_t global_tick = 0;
TCB_t* volatile current_task = 0;
TCB_t* volatile next_task = 0;
TCB_t task_table[MAX_TASKS];
uint8_t task_count = 0;

void Systick_Handler(void){
	global_tick++;

	for (int i = 0; i < task_count; i++){
		if (task_table[i].state == TASK_BLOCKED && task_table[i].delay_ticks > 0){
			task_table[i].delay_ticks--;

			if (task_table[i].delay_ticks == 0) task_table[i].state = TASK_READY;
		}
	}
	RTOS_Scheduling();
}

void RTOS_Init(){
	current_task = 0;
	next_task = 0;
	task_count = 0;

	for (int i = 0; i < MAX_TASKS; i++){
		task_table[i].stack_ptr = 0;
		task_table[i].priority = 255;
		task_table[i].state = TASK_BLOCKED;
		task_table[i].delay_ticks = 0;
	}
	SCB_SHPR3 |= (0xFFUL << 16); //PendSV
	SCB_SHPR3 |= (0xFFUL << 24); //Systick
}

uint8_t RTOS_Task_Create(void (*task_handler)(void),
		uint8_t priority,
		uint32_t *stack_start,
		uint32_t stack_size){

    if (task_count >= MAX_TASKS) return 0;

    uint32_t *top_of_stack = stack_start + stack_size;

    top_of_stack--; *top_of_stack = 0x01000000UL;           //PSR
    top_of_stack--; *top_of_stack = (uint32_t)task_handler; //PC (Program Counter) = Return Address
    top_of_stack--; *top_of_stack = 0xFFFFFFFDUL;           //LR (Link Register)
    top_of_stack--; *top_of_stack = 0x12121212UL;           //R12
    top_of_stack--; *top_of_stack = 0x03030303UL;           //R3
    top_of_stack--; *top_of_stack = 0x02020202UL;           //R2
    top_of_stack--; *top_of_stack = 0x01010101UL;           //R1
    top_of_stack--; *top_of_stack = 0x00000000UL;           //R0

    top_of_stack--; *top_of_stack = 0x11111111UL;           //R11
    top_of_stack--; *top_of_stack = 0x10101010UL;           //R10
    top_of_stack--; *top_of_stack = 0x09090909UL;           //R9
    top_of_stack--; *top_of_stack = 0x08080808UL;           //R8
    top_of_stack--; *top_of_stack = 0x07070707UL;           //R7
    top_of_stack--; *top_of_stack = 0x06060606UL;           //R6
    top_of_stack--; *top_of_stack = 0x05050505UL;           //R5
    top_of_stack--; *top_of_stack = 0x04040404UL;           //R4

    task_table[task_count].stack_ptr = top_of_stack;
    task_table[task_count].priority = priority;
    task_table[task_count].state = TASK_READY;
    task_table[task_count].delay_ticks = 0;

    task_count++;

    return 1;
}
void RTOS_Scheduler_Lauch(){
	uint8_t highest_priority = 255;
	    uint8_t target_index = 0;

	    for (int i = 0; i < task_count; i++){
	        if (task_table[i].state == TASK_READY && task_table[i].priority < highest_priority){
	            highest_priority = task_table[i].priority;
	            target_index = i;
	        }
	    }
	    current_task = &task_table[target_index];
}
void RTOS_Scheduling(){
	uint8_t highest_priority = 255;
	TCB_t* task_t_run = NULL;

	for (int i = 0; i < task_count; i++){
		if (task_table[i].state == TASK_READY){
			if (task_table[i].priority < highest_priority){
				highest_priority = task_table[i].priority;
				task_to_run = &task_table[i];
			}
		}
	}
	if (task_to_run == NULL){
		return; // an Idle Task will be added here later =)))))
	}
	if (task_to_run != current_task){
		next_task = task_to_run;

		SCB_ICSR |= (1 << 28);
	}
}
void RTOS_Systick_Setup(uint32_t frequency){
	uint32_t reload_value = (frequency / 1000) - 1;
	STK_LOAD = reload_value;
	STK_VAL = 0;

	STK_CTRL |= (1 << 0);
	STK_CTRL |= (1 << 1);
	STK_CTRL |= (1 << 2);
}
