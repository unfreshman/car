#include "calculation.h"

#define COMPLEMENTARY_FILTER_GAIN 0.98f

VehicleState state;
float distance,V_A,V_B;
	
void State_Init(void)
{
		state.wheel_track=0;
		state.wheel_radius=0;
	  state.x= 0;
		state.y=0;
		state.theta=0;
		state.v=0;
		state.omega=0;
}

float Forward_Kinematics(VehicleState state,float velocityA,float velocityB,float imu_yaw)
{
		float dt = 10.0 / 1000.0f;
	
    // 计算瞬时速度
    float vB=velocityB * 2 * PI * state.wheel_radius/60.0f;
    float vA=velocityA * 2 * PI * state.wheel_radius/60.0f;
    float v = (vB + vA) / 2.0f;
    
    // 计算理论角速度(角度制)
    float omega_enc = (vA - vB) / state.wheel_track*180/PI;
    
    // IMU数据融合（互补滤波）
    float omega_imu = (imu_yaw - state.theta) / dt; // 近似角速度
    state.omega = (0.7f * omega_enc + 0.3f * omega_imu);          // 加权融合

    // 更新航向角（优先使用IMU数据）
    state.theta = COMPLEMENTARY_FILTER_GAIN * (state.theta + state.omega * dt)
                 + (1 - COMPLEMENTARY_FILTER_GAIN) * imu_yaw;
    
    // 坐标更新
    state.x += v * cosf(state.theta/180*PI) * dt;
    state.y += v * sinf(state.theta/180*PI) * dt;
    state.v = v;
		distance+=v*dt;
    return v;
}

void Inverse_Kinematics(float target_v, float target_omega)	
{
    float target_omega_rad=target_omega/180*PI;
		V_A=target_v-(state.wheel_track*target_omega_rad)/2;
		V_B=target_v+(state.wheel_track*target_omega_rad)/2;
}
