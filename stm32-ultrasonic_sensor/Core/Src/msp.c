#include "main.h"
#include "stm32f4xx_hal_rcc_ex.h"


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

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	GPIO_InitTypeDef tim2OC_gpios;

	// 1. enable the clock
	__HAL_RCC_TIM2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	// 2.Configure the gpios to behave as tim2 cahnnel 1, 2,3, and 4

	tim2OC_gpios.Pin= GPIO_PIN_0;
	tim2OC_gpios.Mode = GPIO_MODE_AF_PP;
	tim2OC_gpios.Pull = GPIO_NOPULL;
	tim2OC_gpios.Speed = GPIO_SPEED_FREQ_LOW;
	tim2OC_gpios.Alternate = GPIO_AF1_TIM2;
	HAL_GPIO_Init(GPIOA, &tim2OC_gpios);

	// 3. NVIC settings
	HAL_NVIC_SetPriority(TIM2_IRQn, 15, 0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
}


void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
	GPIO_InitTypeDef tim3ch1_gpio;

	 // 1. Enable the clock for the timer 3 peripheral
	__HAL_RCC_TIM3_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();


	// 2. Configure a gpio to behave as timer2 channel 1 (alternate function)
	tim3ch1_gpio.Pin = GPIO_PIN_6;
	tim3ch1_gpio.Mode = GPIO_MODE_AF_PP;
	tim3ch1_gpio.Alternate = GPIO_AF2_TIM3;
	HAL_GPIO_Init(GPIOA, &tim3ch1_gpio);

	// 3. NVIC setting
	HAL_NVIC_SetPriority(TIM3_IRQn, 15, 0);
	HAL_NVIC_EnableIRQ(TIM3_IRQn);


}
