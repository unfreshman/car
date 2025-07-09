#include "driver.h"

void motorA_control(float velocityA)
{
	int duty=1000-(fabs(velocityA)/MAX_speed*1000);
	if(velocityA>=0) 
	{
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 1000);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, duty);
	}
	else 
	{
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, duty);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 1000);
	}
}

void motorB_control(float velocityB)
{
	int duty=1000-(fabs(velocityB)/MAX_speed*1000);
	if(velocityB>=0) 
	{
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 1000);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, duty);
	}
	else 
	{
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, duty);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 1000);
	}
}

