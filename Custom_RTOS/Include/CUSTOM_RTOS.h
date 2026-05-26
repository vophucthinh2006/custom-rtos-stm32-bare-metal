#ifndef CUSTOM_RTOS_H
#define CUSTOM_RTOS_H
#include "SCB.h"
#include "STK.h"
#include <stdint.h>

#define MAX_TASKS    10

typedef enum {
    TASK_READY,
    TASK_BLOCKED
} task_state_t;

typedef struct {
    uint32_t *stack_ptr;
    uint32_t priority;
    task_state_t state;
    uint32_t delay_ticks;
} TCB_t;

extern uint32_t global_tick;
extern TCB_t* volatile current_task;
extern TCB_t* volatile next_task;
extern TCB_t task_table[MAX_TASKS];
extern uint8_t task_count;

void RTOS_Init();
uint8_t RTOS_Task_Create(void (*task_handler)(void),
		uint8_t priority,
		uint32_t *stack_start,
		uint32_t stack_size);
void RTOS_Scheduler_Lauch();
void RTOS_Scheduling();
void RTOS_Start(); //UNDERSTAND NOTHING
void RTOS_Systick_Setup(uint32_t frequency);

#endif
