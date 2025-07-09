#ifndef __CALCULATION_H
#define __CALCULATION_H

//#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <math.h>
  
#define PI 3.1415926f

typedef struct{

		float wheel_track;      //轮距
		float wheel_radius;			//轮半径
		float x;                
		float y; 
	  float theta;            //航向角（角度制）
		float v;								//整车线速度
		float omega;						//整车角速度（角度值）
} VehicleState;

extern VehicleState state;
extern float distance,V_A,V_B;

float Forward_Kinematics(VehicleState state,float velocityA,float velocityB,float imu_yaw);
void Inverse_Kinematics(float target_v, float target_omega);
#endif
