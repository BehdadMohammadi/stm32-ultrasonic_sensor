#ifndef INC_MAIN_H_
#define INC_MAIN_H_

#include "stm32f4xx_hal.h"

void SystemClock_Config(void);
void UART2_init(void);
void Error_handler(void);
void TIMER2_Init(void);



#endif /* INC_MAIN_H_ */