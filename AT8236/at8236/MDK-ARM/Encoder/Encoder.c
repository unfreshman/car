#include "Encoder.h"

volatile int encode_countA = 0;
volatile int encode_countB = 0;
int encode_oldA=0;
int encode_oldB=0;
float velocity,vel;
	
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef  *htim)
{
	if(htim->Instance == TIM2)  // ����Ƿ�Ϊ TIM2
    {
  
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim2))/* �ж�CR1��DIRλ */
			{
					encode_countA--;                                      /* DIRλΪ1��Ҳ���ǵݼ����� */
			}
			else
			{
					encode_countA++;                                      /* DIRλΪ0��Ҳ���ǵ������� */
			}
		}
	if(htim->Instance == TIM5)  // ����Ƿ�Ϊ TIM5
    {
    
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim5))/* �ж�CR1��DIRλ */
			{
					encode_countB--;                                      /* DIRλΪ1��Ҳ���ǵݼ����� */
			}
			else
			{
					encode_countB++;                                      /* DIRλΪ0��Ҳ���ǵ������� */
			}
		}
		if(htim->Instance == TIM4)   //10ms�ж�  
		{
							velocity=get_velB();
              vel=pid_velocity(&speed_pid,velocity);
//							long int location=get_encodeB();
//			        printf("%d\n",location);
//              float vel1=pid_location(&location_pid,location);
//							speed_pid.SetPoint =vel1;
//							velocity=get_velB();
//							vel=pid_velocity(&speed_pid,velocity);
//							printf("%.2f\n",velocity);
//			printf("%d\n",get_encodeB());
		}
}

long int get_encodeA(void)
{   uint16_t value_1;
    value_1=__HAL_TIM_GET_COUNTER(&htim2);
	
    /* ���㵱ǰ�ܼ���ֵ����ǰ�ܼ���ֵ = ��������ǰֵ + �������*65536  */
    return ( int32_t )(-(value_1 +encode_countA * 65536));
}

float get_velA(void)
{  
    int encode_nowA = get_encodeA();                         /* ��ȡ��ǰ����ֵ */
    int varA = encode_nowA - encode_oldA;                          /* ��������仯�� */
    encode_oldA = encode_nowA;                                /* ������һ�εļ���ֵ */
    
    return  varA * 100 * 60 / 4 / wire / reduction_ratio ;       /* ���ص���ٶ�ֵ RPM*/
}

long int get_encodeB(void)
{   uint16_t value_2;
    value_2=__HAL_TIM_GET_COUNTER(&htim5);
   
    /* ���㵱ǰ�ܼ���ֵ����ǰ�ܼ���ֵ = ��������ǰֵ + �������*65536  */
    return ( int32_t )(-(value_2 +encode_countB * 65536));
}

float get_velB(void)
{
    int encode_nowB = get_encodeB();                         /* ��ȡ��ǰ����ֵ */
    int varB = encode_nowB - encode_oldB;                          /* ��������仯�� */
    encode_oldB = encode_nowB;                                /* ������һ�εļ���ֵ */
    
    return  varB * 100 * 60 / 4 / wire / reduction_ratio ;       /* ���ص���ٶ�ֵ RPM*/
}
