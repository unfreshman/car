#include "PID.h"

PID_TypeDef  speed_pid;
PID_TypeDef  location_pid; 
void pid_init(void)
{
		speed_pid.SetPoint =-30;       /* 设定目标值 */
		speed_pid.ActualValue = 0.0;  /* 输出期望值清零 */
		speed_pid.SumError = 0.0;     /* 累计偏差 */
		speed_pid.Error = 0.0;        /* Error[1] */
		speed_pid.LastError = 0.0;    /* Error[-1] */
		speed_pid.PrevError = 0.0;    /* Error[-2] */
		speed_pid.Proportion =1.2f;    /* 比例常数 P */
		speed_pid.Integral = 0.15f;      /* 积分常数 I */
		speed_pid.Derivative = 0.0f;    /* 微分常数 D */
	  speed_pid.FilteredFeedback = 0.0; // 初始化滤波值
    speed_pid.Alpha = 0.8;         // 默认滤波系数，根据实际情况调整

		location_pid.SetPoint =14630;       	/* 目标值 */
		location_pid.ActualValue = 0.0;    /* 期望输出值 */
		location_pid.SumError = 0.0;       /* 积分值 */
		location_pid.Error = 0.0;          /* Error[1] */
		location_pid.LastError = 0.0;      /* Error[-1] */
		location_pid.PrevError = 0.0;      /* Error[-2] */
		location_pid.Proportion =1.0f;    /* 比例常数 Proportional Const */
		location_pid.Integral =0;      /* 积分常数 Integral Const */
		location_pid.Derivative = 0;			/* 微分常数 D */
}

float pid_velocity(PID_TypeDef *PID,float velocity)
{
		float Feedback_value=velocity;
		Feedback_value = PID->Alpha * PID->FilteredFeedback + (1 - PID->Alpha) * Feedback_value;
    PID->FilteredFeedback = Feedback_value; // 存储滤波后的值用于下次计算
		printf("%.2f\n",PID->FilteredFeedback);
    PID->Error = (float)(PID->SetPoint - Feedback_value);                   /* 计算偏差 */
		
    /* 增量式PID */
    
    PID->ActualValue += (PID->Proportion * (PID->Error - PID->LastError))                           /* 比例项 */
                        + (PID->Integral * PID->Error)                                              /* 积分项 */
                        + (PID->Derivative * (PID->Error - 2 * PID->LastError + PID->PrevError));   /* 微分项 */
    
    PID->PrevError = PID->LastError;                                        /* 存储偏差，用于下次计算 */
    PID->LastError = PID->Error;
    
		if(PID->ActualValue>MAX_speed*0.6) PID->ActualValue=MAX_speed*0.6;
	  else if(PID->ActualValue<-MAX_speed*0.6) PID->ActualValue=-MAX_speed*0.6;

    return (PID->ActualValue);                                   /* 返回计算后输出的期望值 */
}

float pid_location(PID_TypeDef *PID,float location)
{
		float Feedback_value=location;
    PID->Error = (float)(PID->SetPoint - Feedback_value);                   /* 计算偏差 */
    
	
	  /*位置式*/
    float IntegralTerm ;
		IntegralTerm+= PID->Error;  // 累积积分项
    PID->ActualValue = (PID->Proportion * PID->Error)                   // 比例项
                     + (PID->Integral * IntegralTerm)              // 积分项
                     + (PID->Derivative * (PID->Error - PID->LastError)); // 微分项
    
    PID->LastError = PID->Error;  // 存储当前误差，用于下次计算微分项
//		if(PID->ActualValue>0.6) PID->ActualValue=0.6;
//	  else if(PID->ActualValue<-0.6) PID->ActualValue=-0.6;


    return (PID->ActualValue);                                   /* 返回计算后输出的期望值 */
}
