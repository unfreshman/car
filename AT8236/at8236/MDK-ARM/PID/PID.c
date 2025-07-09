#include "PID.h"

PID_TypeDef  speed_pid;
PID_TypeDef  location_pid; 
void pid_init(void)
{
		speed_pid.SetPoint =-30;       /* �趨Ŀ��ֵ */
		speed_pid.ActualValue = 0.0;  /* �������ֵ���� */
		speed_pid.SumError = 0.0;     /* �ۼ�ƫ�� */
		speed_pid.Error = 0.0;        /* Error[1] */
		speed_pid.LastError = 0.0;    /* Error[-1] */
		speed_pid.PrevError = 0.0;    /* Error[-2] */
		speed_pid.Proportion =1.2f;    /* �������� P */
		speed_pid.Integral = 0.15f;      /* ���ֳ��� I */
		speed_pid.Derivative = 0.0f;    /* ΢�ֳ��� D */
	  speed_pid.FilteredFeedback = 0.0; // ��ʼ���˲�ֵ
    speed_pid.Alpha = 0.8;         // Ĭ���˲�ϵ��������ʵ���������

		location_pid.SetPoint =14630;       	/* Ŀ��ֵ */
		location_pid.ActualValue = 0.0;    /* �������ֵ */
		location_pid.SumError = 0.0;       /* ����ֵ */
		location_pid.Error = 0.0;          /* Error[1] */
		location_pid.LastError = 0.0;      /* Error[-1] */
		location_pid.PrevError = 0.0;      /* Error[-2] */
		location_pid.Proportion =1.0f;    /* �������� Proportional Const */
		location_pid.Integral =0;      /* ���ֳ��� Integral Const */
		location_pid.Derivative = 0;			/* ΢�ֳ��� D */
}

float pid_velocity(PID_TypeDef *PID,float velocity)
{
		float Feedback_value=velocity;
		Feedback_value = PID->Alpha * PID->FilteredFeedback + (1 - PID->Alpha) * Feedback_value;
    PID->FilteredFeedback = Feedback_value; // �洢�˲����ֵ�����´μ���
		printf("%.2f\n",PID->FilteredFeedback);
    PID->Error = (float)(PID->SetPoint - Feedback_value);                   /* ����ƫ�� */
		
    /* ����ʽPID */
    
    PID->ActualValue += (PID->Proportion * (PID->Error - PID->LastError))                           /* ������ */
                        + (PID->Integral * PID->Error)                                              /* ������ */
                        + (PID->Derivative * (PID->Error - 2 * PID->LastError + PID->PrevError));   /* ΢���� */
    
    PID->PrevError = PID->LastError;                                        /* �洢ƫ������´μ��� */
    PID->LastError = PID->Error;
    
		if(PID->ActualValue>MAX_speed*0.6) PID->ActualValue=MAX_speed*0.6;
	  else if(PID->ActualValue<-MAX_speed*0.6) PID->ActualValue=-MAX_speed*0.6;

    return (PID->ActualValue);                                   /* ���ؼ�������������ֵ */
}

float pid_location(PID_TypeDef *PID,float location)
{
		float Feedback_value=location;
    PID->Error = (float)(PID->SetPoint - Feedback_value);                   /* ����ƫ�� */
    
	
	  /*λ��ʽ*/
    float IntegralTerm ;
		IntegralTerm+= PID->Error;  // �ۻ�������
    PID->ActualValue = (PID->Proportion * PID->Error)                   // ������
                     + (PID->Integral * IntegralTerm)              // ������
                     + (PID->Derivative * (PID->Error - PID->LastError)); // ΢����
    
    PID->LastError = PID->Error;  // �洢��ǰ�������´μ���΢����
//		if(PID->ActualValue>0.6) PID->ActualValue=0.6;
//	  else if(PID->ActualValue<-0.6) PID->ActualValue=-0.6;


    return (PID->ActualValue);                                   /* ���ؼ�������������ֵ */
}
