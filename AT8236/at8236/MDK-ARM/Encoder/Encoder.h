#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm32f4xx_hal.h"
#include "tim.h"
#include "PID.h"

#define wire 11
#define reduction_ratio 34

extern float velocity,vel;

long int get_encodeA(void);
float get_velA(void);
long int get_encodeB(void);
float get_velB(void);

#endif
