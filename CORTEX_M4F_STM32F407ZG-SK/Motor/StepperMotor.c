#include "StepperMotor.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"


//clockwise
uint8_t cw_step[8][4]={ {1,0,0,0},{1,0,1,0},{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,1,0,1},{0,0,0,1},{1,0,0,1} };
//counter clockwise
uint8_t ccw_step[8][4]={ {1,0,0,1},{0,0,0,1},{0,1,0,1},{0,1,0,0},{0,1,1,0},{0,0,1,0},{1,0,1,0},{1,0,0,0} };
uint16_t MotorY1 = GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7;
uint16_t MotorY2 = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
uint16_t MotorYs[]= { {GPIO_Pin_2,GPIO_Pin_4,GPIO_Pin_5,GPIO_Pin_7},{GPIO_Pin_2,GPIO_Pin_3,GPIO_Pin_4,GPIO_Pin_5} };              



void GPIO_YMotor_init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);

	GPIO_InitTypeDef gpio;
	GPIO_StructInit(&gpio);
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_Pin = MotorY1;
	gpio.GPIO_PuPd=GPIO_PuPd_NOPULL;
	gpio.GPIO_OType=GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_100MHz;
	//	GPIO_Init( GPIOD , &gpio );

	gpio.GPIO_Pin = MotorY2;
	GPIO_Init(GPIOE,&gpio);

	while(1)
	{
		STM_EVAL_LEDToggle(LED3);
		STM_EVAL_LEDToggle(LED4);
		delay(1000);
		STM_EVAL_LEDOff(LED3);
		STM_EVAL_LEDOff(LED4);
		delay(1000);                                                                                               
	}
}

//'motor' for choosing motors, 0 for Y1, 1 for Y2
//'cw' for direction, 1->cw , -1->ccw
//'speed' should between 40~1000
// should consider the initial position
void MotorY_loop(int motor,int cw,int steps,int speed,int *st)
{
	//speed
	uint8_t j;
	uint8_t i;
	if(speed<40) speed=40;

	for(i=0;i<steps;i++)
	{
		//move one step
		for(j=0;j<4;j++)
		{
			if(cw==1)//cw
			{
				if(cw_step[i%8][j]==0)
				{
					if(motor==0)//Y1
						GPIO_ResetBits(GPIOD,MotorYs[motor]);
					else if (motor==1)
						GPIO_ResetBits(GPIOE,MotorYs[motor]);
				}
				else if(cw_step[i%8][j]==1)
				{
					if(motor==0)//Y1
						GPIO_SetBits(GPIOD,MotorYs[motor]);
					else if (motor==1)
						GPIO_SetBits(GPIOE,MotorYs[motor]);
				}
			}
			else//ccw 
			{
				if(ccw_step[i%8][j]==0)
				{
					if(motor==0)//Y1
						GPIO_ResetBits(GPIOD,MotorYs[motor]);
					else if (motor==1)
						GPIO_ResetBits(GPIOE,MotorYs[motor]);
				}
				else if(ccw_step[i%8][j]==1)
				{
					if(motor==0)//Y1
						GPIO_SetBits(GPIOD,MotorYs[motor]);
					else if (motor==1)
						GPIO_SetBits(GPIOE,MotorYs[motor]);
				}
			}
		}
		delay(speed);
	}
}


void delay(uint32_t ms)
{
	ms *=3360;
	while(ms--)
		__NOP();
}
