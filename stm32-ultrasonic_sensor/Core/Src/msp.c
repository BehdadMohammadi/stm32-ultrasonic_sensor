#include "main.h"

void HAL_MspInit(void)
{

	// 1. setup priority grouping of the arm cortex mx processor
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
    
    // 2. Enable the required system exception of the arm cortex mx processor
	SCB->SHCSR |= 0x7 << 16;

}


void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef gpio_uart;
	
    //1. enable the clock for the USART2 peripheral as well as for GPIOA peripheral
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
    //2. Do the pin muxing configuration
	gpio_uart.Pin = GPIO_PIN_2;
	gpio_uart.Mode = GPIO_MODE_AF_PP;
	gpio_uart.Pull = GPIO_PULLUP;
	gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
	gpio_uart.Alternate = GPIO_AF7_USART2; //UART2_TX
	HAL_GPIO_Init(GPIOA, &gpio_uart);
	
    //3. Enable the IRQ and set up the priority (NVIC setting)
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn, 15, 0);

}