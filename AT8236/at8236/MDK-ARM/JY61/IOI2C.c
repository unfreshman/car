#include "IOI2C.h"


void Delay(uint32_t count)//400KHzIIC
{
	unsigned int uiCnt = count*8;
	while (uiCnt --);
}
//static void IIC_Delay(void)
//{
//	int i=0;
//	for(i=0;i<40;i++);
//}

void loSetOutput(uint16_t GPIO_Pin)
{
		GPIO_InitTypeDef GPIO_InitStructure;
    // 配置 GPIO 引脚
    GPIO_InitStructure.Pin = GPIO_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;  // 推挽输出模式
    GPIO_InitStructure.Pull = GPIO_PULLUP;  // 上拉模式
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;  // 中等速度，对应 50MHz
    // 初始化 GPIO 引脚
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void loSetInput(uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStructure1;
    // 配置 GPIO 引脚
    GPIO_InitStructure1.Pin = GPIO_Pin;
    GPIO_InitStructure1.Mode = GPIO_MODE_INPUT;  // 推挽输出模式
    GPIO_InitStructure1.Pull = GPIO_PULLUP;  // 上拉模式
    GPIO_InitStructure1.Speed = GPIO_SPEED_FREQ_HIGH;  // 中等速度，对应 50MHz
    // 初始化 GPIO 引脚
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure1);
	
}

void IIC_Init(void)
{			
	SDA_OUT();     
	IIC_SDA_H;	  	  
	IIC_SCL_H;
}

void IIC_Start(void)
{
	SDA_OUT();    
	IIC_SDA_H;	  	  
	IIC_SCL_H;
//	IIC_Delay();
	Delay(5);
 	IIC_SDA_L;//START:when CLK is high,DATA change form high to low 
//	IIC_Delay();
	Delay(5);
	IIC_SCL_L;
}
	  
void IIC_Stop(void)
{
	SDA_OUT();
	IIC_SCL_L;
	IIC_SDA_L;//STOP:when CLK is high DATA change form low to high
	
		Delay(5);
//	IIC_Delay();
	IIC_SCL_H; 
	IIC_SDA_H;
	
		Delay(5);	
//	IIC_Delay();	
}

uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0; 
	SDA_IN();     
	IIC_SDA_H;
		Delay(5);
//	IIC_Delay();
	while(IIC_SDA_STATUS)
	{
		ucErrTime++;
		if(ucErrTime>50)
		{
			IIC_Stop();
			return 1;
		}
		Delay(5);
//		IIC_Delay();
	}  
	IIC_SCL_H;
	Delay(5);
//	IIC_Delay();
	IIC_SCL_L;
	 
	return 0;  
} 

void IIC_Ack(void)
{
	IIC_SCL_L;
	SDA_OUT();
	IIC_SDA_L;
	
		Delay(5);
//	IIC_Delay();
	IIC_SCL_H;
		Delay(5);
//	IIC_Delay();
	IIC_SCL_L;
}
	    
void IIC_NAck(void)
{
	IIC_SCL_L;
	SDA_OUT();
	IIC_SDA_H;

		Delay(5);
//	IIC_Delay();
	IIC_SCL_H;
		Delay(5);
//	IIC_Delay();
	IIC_SCL_L;
}					 				     
		  
void IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t; 
		SDA_OUT(); 	    
    IIC_SCL_L;
    for(t=0;t<8;t++)
    {              
        if(txd&0x80)
				{
					IIC_SDA_H;
				}
				else
				{
					IIC_SDA_L;
				}
       // txd<<=1; 	  
			
		Delay(2); 
//		IIC_Delay();
		IIC_SCL_H;
		Delay(5);
//		IIC_Delay();
		txd<<=1; 	
		IIC_SCL_L;	
			
		Delay(3);
//		IIC_Delay();
    }	 
} 	 
  
uint8_t IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();
    for(i=0;i<8;i++ )
	{
        IIC_SCL_L; 
        
		Delay(5);
//		IIC_Delay();
		IIC_SCL_H;
        receive<<=1;
        if(IIC_SDA_STATUS)receive++;   

		Delay(5); 
//		IIC_Delay();
    }					 
    if (ack)
        IIC_Ack(); 
    else
        IIC_NAck();
    return receive;
}

int32_t IICreadBytes(uint8_t dev, uint8_t reg, uint8_t *data, uint32_t length)
{
    uint32_t count = 0;

    IIC_Start();
    IIC_Send_Byte(dev);	
    if(IIC_Wait_Ack() == 1)return 0;
    IIC_Send_Byte(reg);
    if(IIC_Wait_Ack() == 1)return 0;
    IIC_Start();
    IIC_Send_Byte(dev+1); 
    if(IIC_Wait_Ack() == 1)return 0;

    for(count=0; count<length; count++)
    {
        if(count!=length-1)
				{
					data[count]=IIC_Read_Byte(1);
				//	printf("%d \r\n",data[count]);
				}
        else  data[count]=IIC_Read_Byte(0);	 
    }
    IIC_Stop();
				
    return 1;
}


int32_t IICwriteBytes(uint8_t dev, uint8_t reg, uint8_t* data, uint32_t length)
{
    uint32_t count = 0;
    IIC_Start();
    IIC_Send_Byte(dev);	   
    if(IIC_Wait_Ack() == 1)return 0;
    IIC_Send_Byte(reg);   
    if(IIC_Wait_Ack() == 1)return 0;
    for(count=0; count<length; count++)
    {
        IIC_Send_Byte(data[count]);

        if(IIC_Wait_Ack() == 1)return 0;
    }
    IIC_Stop();

    return 1; 
}
