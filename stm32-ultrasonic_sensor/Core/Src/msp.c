#include "main.h"

void HAL_MspInit(void)
{

	// Here will do low level processor spesific inits.

		// 1. setup priority grouping of the arm cortex mx processor
		HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

		// 2. Enable the required system exception of the arm cortex mx processor
		SCB->SHCSR |= 0x7 << 16;

		// 3. configure the priority for the system exceptions
}