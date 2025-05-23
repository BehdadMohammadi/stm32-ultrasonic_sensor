#include "stm32f4xx_hal.h"
#include "main.h"
#include <stdio.h>
#include <string.h>


UART_HandleTypeDef huart2;
TIM_HandleTypeDef htimer2;

char* user_data = "Behdad is Here\r\n";


int main(void)
{

	HAL_Init();

    SystemClock_Config();

    UART2_init();

	// if (HAL_UART_Transmit(&huart2, (uint8_t*)user_data, (uint16_t)strlen((char *)user_data), HAL_MAX_DELAY) != HAL_OK)
	// {
	// 	Error_handler();
	// }

	TIMER2_Init();

	if (HAL_TIM_PWM_Start(&htimer2, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_handler();
	}


	while(1);

	return 0;
}

void SystemClock_Config(void)
{

}

void UART2_init(void)
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

void Error_handler(void)
{
    while(1);
}

void TIMER2_Init(void)
{
	TIM_OC_InitTypeDef tim2PWM_Config;

	// 1 second period generates here
	htimer2.Instance = TIM2;

	htimer2.Init.Period = 1000000-1;
	htimer2.Init.Prescaler = 15;
	if (HAL_TIM_PWM_Init(&htimer2) != HAL_OK)
	{
		Error_handler();
	}

	memset(&tim2PWM_Config, 0, sizeof(tim2PWM_Config));

	tim2PWM_Config.OCMode = TIM_OCMODE_PWM1;
	tim2PWM_Config.OCPolarity = TIM_OCPOLARITY_HIGH;
	tim2PWM_Config.Pulse = (htimer2.Init.Period*0.001)/100;

	if (HAL_TIM_PWM_ConfigChannel(&htimer2, &tim2PWM_Config, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_handler();
	}

	// tim2PWM_Config.Pulse = (htimer2.Init.Period*45)/100;
	// if (HAL_TIM_PWM_ConfigChannel(&htimer2, &tim2PWM_Config, TIM_CHANNEL_2) != HAL_OK)
	// {
	// 	Error_handler();
	// }

	// tim2PWM_Config.Pulse = (htimer2.Init.Period*75)/100;
	// if (HAL_TIM_PWM_ConfigChannel(&htimer2, &tim2PWM_Config, TIM_CHANNEL_3) != HAL_OK)
	// {
	// 	Error_handler();
	// }

	// tim2PWM_Config.Pulse = (htimer2.Init.Period*95)/100;
	// if (HAL_TIM_PWM_ConfigChannel(&htimer2, &tim2PWM_Config, TIM_CHANNEL_4) != HAL_OK)
	// {
	// 	Error_handler();
	// }

}
