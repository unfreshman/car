#ifndef __PID_H
#define __PID_H

#include "driver.h"

typedef struct
{
     float  SetPoint;            /* Ŀ��ֵ */
     float  ActualValue;         /* �������ֵ */
     float  SumError;            /* �ۼ�ƫ�� */
     float  Proportion;          /* �������� P */
     float  Integral;            /* ���ֳ��� I */
     float  Derivative;          /* ΢�ֳ��� D */
     float  Error;               /* Error[1] */
     float  LastError;           /* Error[-1] */
     float  PrevError;           /* Error[-2] */
		 float  FilteredFeedback; 		// �˲���ķ���ֵ
		 float  Alpha;            		// ��ͨ�˲�ϵ�� (ȡֵ��Χ0.0~1.0)
} PID_TypeDef;

extern PID_TypeDef  speed_pid;
extern PID_TypeDef  location_pid;

void pid_init(void);
float pid_velocity(PID_TypeDef *PID,float velocity);
float pid_location(PID_TypeDef *PID,float location);
#endif
