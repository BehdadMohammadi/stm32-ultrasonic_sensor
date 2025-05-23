#include "main.h"

void HAL_MspInit(void)
{

	// 1. setup priority grouping of the arm cortex mx processor
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
    
    // 2. Enable the required system exception of the arm cortex mx processor
	SCB->SHCSR |= 0x7 << 16;

}
