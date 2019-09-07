#ifndef _PID_H
#define _PID_H

#include "stm32f1xx_hal.h"

void PID_init(void);
float PID_realize(float speed);

#endif
