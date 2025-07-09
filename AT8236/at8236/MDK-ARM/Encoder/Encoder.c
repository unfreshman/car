#include "Encoder.h"

volatile int encode_countA = 0;
volatile int encode_countB = 0;
int encode_oldA=0;
int encode_oldB=0;
float velocity,vel;
	
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef  *htim)
{
	if(htim->Instance == TIM2)  // 检查是否为 TIM2
    {
  
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim2))/* 判断CR1的DIR位 */
			{
					encode_countA--;                                      /* DIR位为1，也就是递减计数 */
			}
			else
			{
					encode_countA++;                                      /* DIR位为0，也就是递增计数 */
			}
		}
	if(htim->Instance == TIM5)  // 检查是否为 TIM5
    {
    
		if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim5))/* 判断CR1的DIR位 */
			{
					encode_countB--;                                      /* DIR位为1，也就是递减计数 */
			}
			else
			{
					encode_countB++;                                      /* DIR位为0，也就是递增计数 */
			}
		}
		if(htim->Instance == TIM4)   //10ms中断  
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
	
    /* 计算当前总计数值，当前总计数值 = 计数器当前值 + 溢出次数*65536  */
    return ( int32_t )(-(value_1 +encode_countA * 65536));
}

float get_velA(void)
{  
    int encode_nowA = get_encodeA();                         /* 获取当前计数值 */
    int varA = encode_nowA - encode_oldA;                          /* 计算计数变化量 */
    encode_oldA = encode_nowA;                                /* 保存这一次的计数值 */
    
    return  varA * 100 * 60 / 4 / wire / reduction_ratio ;       /* 返回电机速度值 RPM*/
}

long int get_encodeB(void)
{   uint16_t value_2;
    value_2=__HAL_TIM_GET_COUNTER(&htim5);
   
    /* 计算当前总计数值，当前总计数值 = 计数器当前值 + 溢出次数*65536  */
    return ( int32_t )(-(value_2 +encode_countB * 65536));
}

float get_velB(void)
{
    int encode_nowB = get_encodeB();                         /* 获取当前计数值 */
    int varB = encode_nowB - encode_oldB;                          /* 计算计数变化量 */
    encode_oldB = encode_nowB;                                /* 保存这一次的计数值 */
    
    return  varB * 100 * 60 / 4 / wire / reduction_ratio ;       /* 返回电机速度值 RPM*/
}
