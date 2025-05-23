#include "stm32f4xx_hal.h"
#include "main.h"
#include <stdio.h>
#include <string.h>


int main(void)
{

	HAL_Init();

    SystemClock_Config();

    UART2_init();

	while(1);

	return 0;
}

void SystemClock_Config(void)
{

}

void UART2_init()
{
    
}