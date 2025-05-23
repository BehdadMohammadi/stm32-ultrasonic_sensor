#ifndef INC_MAIN_H_
#define INC_MAIN_H_

#include "stm32f4xx_hal.h"

void SystemClock_Config(void);

void UART2_init();

void Error_handler();

#endif /* INC_MAIN_H_ */