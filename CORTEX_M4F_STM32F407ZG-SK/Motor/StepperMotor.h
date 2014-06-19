/*
   Using  { PE2,PE3,PE4,P45 } for motor at one of y axis->Y1
   		  {	PD2,PD4,PD5,PD7 } for motor at one of y axis->Y2
		  
 
*/

#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include"stm32f4xx.h"
#include"stm32f4xx_gpio.h"
#include"stm32f4xx_rcc.h"

//pins D
const uint16_t MotorY1 = GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7;

//pins E
const uint16_t MotorY2 = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;

//0->Y1 , 1->Y2
const uint16_t MotorYs[] = { {GPIO_Pin_2,GPIO_Pin_4,GPIO_Pin_5,GPIO_Pin_7},{GPIO_Pin_2,GPIO_Pin_3,GPIO_Pin_4,GPIO_Pin_5} };

void GPIO_YMotor_init();

void MotorY_loop(int motor,int cw,int steps,int speed,int *st);
void delay(uint32_t ms);

#endif
