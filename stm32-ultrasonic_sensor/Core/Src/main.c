#include "stm32f4xx_hal.h"
#include "main.h"
#include <stdio.h>
#include <string.h>


UART_HandleTypeDef huart2;


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

    huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX;

	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_handler();
	}

}

void Error_handler()
{
    while(1);
}