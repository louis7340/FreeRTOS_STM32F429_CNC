/*
	for T13596AA Stepper Motor with STM32F429 Discovery


   */

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#define STEPS 8


const LED= GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
const LEDS[4]={GPIO_Pin_2,GPIO_Pin_3, GPIO_Pin_4, GPIO_Pin_5};
const uint8_t cw_step[STEPS][4]={ {1,0,0,0},{1,0,1,0},{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,1,0,1},{0,0,0,1},{1,0,0,1} };
const uint8_t ccw_step[STEPS][4]={ {1,0,0,1},{0,0,0,1},{0,1,0,1},{0,1,0,0},{0,1,1,0},{0,0,1,0},{1,0,1,0},{1,0,0,0} };
//const uint8_t cw_step[STEPS][4]={ {1,1,0,0},{0,1,1,0},{0,0,1,1},{1,0,0,1}};
//const uint8_t ccw_step[STEPS][4]={ {1,1,0,0},{1,0,0,1},{0,0,1,1},{0,1,1,0}};
uint32_t i=0;

void init()
{
	GPIO_InitTypeDef gpio;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);


	gpio.GPIO_Mode=GPIO_Mode_OUT;
	gpio.GPIO_OType=GPIO_OType_PP;
	gpio.GPIO_Pin= LED;
	gpio.GPIO_PuPd=GPIO_PuPd_NOPULL;
	gpio.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOE,&gpio);
}


void loop()
{
	uint8_t j;
	for(j=0;j<4;j++)
	{
		if(ccw_step[i][j]==0)
			GPIO_ResetBits(GPIOE,LEDS[j]);
		else GPIO_SetBits(GPIOE,LEDS[j]);
	}
	//fastest to 40
	delay(100);
	i=(i+1)%STEPS;
}




void delay(uint32_t ms)
{
	ms*=3360;
	while(ms--)
		__NOP();
}

int main()
{
	init();
	/*for(int k=0;k<4;k++)
	  {
	  for(int j=0;j<4;j++)
	  {
	  if(step[i%4][j]==0)
	  GPIO_ResetBits(GPIOG,LEDS[j]);
	  else GPIO_SetBits(GPIOG,LEDS[j]);
	  }
	  }*/
	while(1)
	{
		loop();
	}while(1);
}
