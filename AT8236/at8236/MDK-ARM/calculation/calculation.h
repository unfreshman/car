#ifndef __CALCULATION_H
#define __CALCULATION_H

//#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <math.h>
  
#define PI 3.1415926f

typedef struct{

		float wheel_track;      //�־�
		float wheel_radius;			//�ְ뾶
		float x;                
		float y; 
	  float theta;            //����ǣ��Ƕ��ƣ�
		float v;								//�������ٶ�
		float omega;						//�������ٶȣ��Ƕ�ֵ��
} VehicleState;

extern VehicleState state;
extern float distance,V_A,V_B;

float Forward_Kinematics(VehicleState state,float velocityA,float velocityB,float imu_yaw);
void Inverse_Kinematics(float target_v, float target_omega);
#endif
