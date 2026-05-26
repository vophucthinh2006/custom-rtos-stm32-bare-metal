# Custom RTOS – Bare-Metal STM32 (not completed yet)

A lightweight, priority-based Real-Time Operating System (RTOS) implemented from scratch on STM32 using direct register-level programming. This project focuses on manual context switching, dual-stack isolation, deterministic preemption, and custom memory block allocation without using any third-party libraries—including CMSIS.

## 1. Project Overview

This project implements a custom real-time operating system kernel on the STM32 platform. The core scheduler manages multiple user tasks concurrently using an $O(n)$ preemptive priority-based scheduling algorithm. Timing ticks are driven directly by raw hardware timer registers, while inter-task communication is synchronized using custom counting semaphores.

Memory management is handled via a predictable, thread-safe static memory pool allocator rather than standard non-deterministic dynamic allocation. System execution is split cleanly between kernel operations running on the Main Stack Pointer (MSP) and isolated user tasks running on the Process Stack Pointer (PSP).

## 2. Learning Objectives

* Practice bare-metal operating system design on STM32 without using HAL, LL, or CMSIS libraries.
* Understand ARM Cortex-M3 core peripherals (SysTick, SCB, NVIC) and core registers (`R0`-`R15`, `CONTROL`, `xPSR`) at the silicon level.
* Master the mechanics of manual hardware and software exception stacking for context switching.
* Implement a preemptive, priority-driven multitasking scheduler kernel.
* Design thread-safe, deterministic inter-task synchronization structures and memory partitioners.

## 3. Hardware Overview

* **MCU:** STM32F103C8T6 (ARM Cortex-M3 core).
* **Clock:** 8 MHz internal clock (default configuration) and 72 MHz PLL-based clock (for high-speed testing).
* **Core Peripherals:** Core SysTick Timer, System Control Block (SCB), and Nested Vectored Interrupt Controller (NVIC).
* **Memory Constraints:** 20 KB SRAM partitioned into individual static task stacks and kernel space.
* **Programming:** ST-Link V2.
* **Development Style:** 100% Bare metal (direct core pointer register mapping).

## 4. Author

Author: Vo Phuc Thinh.
