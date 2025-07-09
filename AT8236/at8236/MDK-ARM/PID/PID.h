#ifndef __PID_H
#define __PID_H

#include "driver.h"

typedef struct
{
     float  SetPoint;            /* 目标值 */
     float  ActualValue;         /* 期望输出值 */
     float  SumError;            /* 累计偏差 */
     float  Proportion;          /* 比例常数 P */
     float  Integral;            /* 积分常数 I */
     float  Derivative;          /* 微分常数 D */
     float  Error;               /* Error[1] */
     float  LastError;           /* Error[-1] */
     float  PrevError;           /* Error[-2] */
		 float  FilteredFeedback; 		// 滤波后的反馈值
		 float  Alpha;            		// 低通滤波系数 (取值范围0.0~1.0)
} PID_TypeDef;

extern PID_TypeDef  speed_pid;
extern PID_TypeDef  location_pid;

void pid_init(void);
float pid_velocity(PID_TypeDef *PID,float velocity);
float pid_location(PID_TypeDef *PID,float location);
#endif
