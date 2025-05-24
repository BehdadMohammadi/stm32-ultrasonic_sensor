#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_def.h"
#include "main.h"
#include <stdio.h>
#include <string.h>


UART_HandleTypeDef huart2;

TIM_HandleTypeDef htimer2;
TIM_HandleTypeDef htimer3;


uint32_t input_capture[2] = {0};
uint8_t count = 1;
uint8_t is_capture_done = TRUE;

uint32_t capture_difference = 0;
double time3_cnt_freq = 0;
double time3_cnt_res = 0;
double user_signal_time_period = 0;
double user_signal_time_freq = 0;
char usr_msg[500];

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


	TIMER3_Init();

	if (HAL_TIM_IC_Start_IT(&htimer3, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_handler();
	}


	while(1)
	{
		if (is_capture_done)
		{
			if (input_capture[1] > input_capture[0])
			{
				capture_difference = input_capture[1] - input_capture[0];
			}
			else
			{
				capture_difference = (0xFFFF - input_capture[0]) + input_capture[1];
			}


			time3_cnt_freq = (HAL_RCC_GetPCLK1Freq()*2)/(htimer3.Init.Prescaler+1);
			time3_cnt_res = 1/time3_cnt_freq;
			user_signal_time_period = capture_difference*time3_cnt_res;
			user_signal_time_freq = 1/user_signal_time_period;

			sprintf(usr_msg, "Frequency of the signal applied = %f\r\n", user_signal_time_freq);
			HAL_UART_Transmit(&huart2, (uint8_t*)usr_msg, strlen(usr_msg), HAL_MAX_DELAY);


			is_capture_done = FALSE;
		}
	}

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
	htimer2.Init.Period = 16000000-1;
	htimer2.Init.Prescaler = 0;
	if (HAL_TIM_PWM_Init(&htimer2) != HAL_OK)
	{
		Error_handler();
	}

	memset(&tim2PWM_Config, 0, sizeof(tim2PWM_Config));

	tim2PWM_Config.OCMode = TIM_OCMODE_PWM1;
	tim2PWM_Config.OCPolarity = TIM_OCPOLARITY_HIGH;
	// 10 micro second high signal
	tim2PWM_Config.Pulse = (htimer2.Init.Period*0.001)/100;

	if (HAL_TIM_PWM_ConfigChannel(&htimer2, &tim2PWM_Config, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_handler();
	}

}

void TIMER3_Init(void)
{
	TIM_IC_InitTypeDef timer3IC_Config;

	htimer3.Instance = TIM3;
	htimer3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htimer3.Init.Period = 0xFFFF;
	htimer3.Init.Prescaler = 1;
	if (HAL_TIM_IC_Init(&htimer3) != HAL_OK)
	{
		Error_handler();
	}

	timer3IC_Config.ICFilter = 0;
	timer3IC_Config.ICPolarity = TIM_ICPOLARITY_RISING;
	timer3IC_Config.ICPrescaler = TIM_ICPSC_DIV1;
	timer3IC_Config.ICSelection = TIM_ICSELECTION_DIRECTTI;
	if (HAL_TIM_IC_ConfigChannel(&htimer3, &timer3IC_Config, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_handler();
	}
}


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (!is_capture_done)
	{
		if (count == 1)
		{
			input_capture[0] = __HAL_TIM_GET_COMPARE(htim, TIM_CHANNEL_1);
			count++;
		}
		else if (count == 2)
		{
			input_capture[1] = __HAL_TIM_GET_COMPARE(htim, TIM_CHANNEL_1);
			count = 1;
			is_capture_done = TRUE;
		}

	}
}
