#ifndef  __SPISLAVE_H
#define  __SPISLAVE_H
#include "stm32f10x.h"
extern  uint8_t testValue;

void spiSlaveInit(void);
void spiGpioInit(void);
void spiModeInit(void);
void nvicConfig(void);

#endif /*__SPISLAVE_H*/

