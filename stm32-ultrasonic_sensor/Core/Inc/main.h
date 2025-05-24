#ifndef INC_MAIN_H_
#define INC_MAIN_H_

#include "stm32f4xx_hal.h"

void SystemClock_Config(void);
void UART2_init(void);
void Error_handler(void);
void TIMER2_Init(void);
void TIMER3_Init(void);

#define TRUE 1
#define FALSE 0



#endif /* INC_MAIN_H_ */