#ifndef __DRIVER_H
#define __DRIVER_H

#include "stm32f4xx_hal.h"
#include "tim.h"
#include "math.h"

#define MAX_speed 170

	
void motorA_control(float velocityA);
void motorB_control(float velocityB);
#endif
