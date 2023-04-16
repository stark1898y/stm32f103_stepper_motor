/*
 * @Author       : yzy
 * @Date         : 2023-04-15 22:11:50
 * @LastEditors  : yzy
 * @LastEditTime : 2023-04-16 01:02:33
 * @FilePath     : \stm32f103_stepper_motor\BSP\stepper_motor\bsp_stepper_motor.h
 * @Description  :
 *
 * Copyright (c) 2023 by yzy, All Rights Reserved.
 */
#ifndef __STEPPER_kMotorH__
#define __STEPPER_kMotorH__

#include "bsp_sys.h"

// #define kMotorA_PIN
typedef enum
{
	kMotorCw = 0U,       //  顺时针旋转
	kMotorAcw       //  逆时针旋转
} TeMotorDirection;

typedef enum
{
	kMotorStop = 0U,
    kMotorRun
} TeMotorControl;

typedef enum {
    kMotorLoop = 0U, //  一直旋转
    kMotorStep       //  精准控制步数
} TeMotorMode;

typedef enum
{
    kMotorSpeedLow = 15,
    kMotorSpeedMed = 10,
    kMotorSpeedHigh = 5
} TeMotorSpeed; //  speed越小，电机速度越快

typedef enum
{
    kLineA = 0U,
    kLineB,
    kLineC,
    kLineD,
} TeMotorGpioLine;

typedef enum
{
    kBeatA = 0U,
    kBeatAb,
    kBeatB,
    kBeatBc,
    kBeatC,
    kBeatCd,
    kBeatD,
    kBeatDa,
    kBeatOff
} TeMotorBeat;

typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;
} TsStepperMotorGpio;

typedef struct
{
    uint8_t ticks;        //  定时器中的计数变量
    uint8_t beat;         //  步进电机的控制节拍索引(0~7)
    uint32_t step;        //  步进电机旋转相应的步数
    TeMotorControl control;   //  kMotorLoop:一直旋转  kMotorStep:精准控制步数
    TeMotorDirection dir;
    TeMotorMode mode;     //  kMotorSTOP/kMotorCW/kMotorCCW
    TeMotorSpeed speed;   //  kMotorSPEED_LOW~kMotorSPEED_HIGH

    TsStepperMotorGpio Gpio[4];
} TsStepperMotor;

// void (*MotorAction_Cb)(TsStepperMotor* pMotor, uint8_t beat);

#if 0
  //  A相通电，其他相断
#define Coil1_A()   do {
                        HAL_GPIO_WritePin(MOTOR_A_GPIO_Port, MOTOR_B_Pin);
                        A1_PIN = 1;
                        B1_PIN = 0;
                        C1_PIN = 0;
                        D1_PIN = 0;
                    } while(0U)

#define Coil1_AB  {A1_PIN = 1; B1_PIN = 1; C1_PIN = 0; D1_PIN = 0; }  //  AB相通电
#define Coil1_B   {A1_PIN = 0; B1_PIN = 1; C1_PIN = 0; D1_PIN = 0; }  //  B相通电，其他相断
#define Coil1_BC  {A1_PIN = 0; B1_PIN = 1; C1_PIN = 1; D1_PIN = 0; }  //  BC相通电，其他相断
#define Coil1_C   {A1_PIN = 0; B1_PIN = 0; C1_PIN = 1; D1_PIN = 0; }  //  C相通电，其他相断
#define Coil1_CD  {A1_PIN = 0; B1_PIN = 0; C1_PIN = 1; D1_PIN = 1; }  //  CD相通电，其他相断
#define Coil1_D   {A1_PIN = 0; B1_PIN = 0; C1_PIN = 0; D1_PIN = 1; }  //  D相通电，其他相断
#define Coil1_DA  {A1_PIN = 1; B1_PIN = 0; C1_PIN = 0; D1_PIN = 1; }  //  AD相通电，其他相断
#define Coil1_OFF {A1_PIN = 0; B1_PIN = 0; C1_PIN = 0; D1_PIN = 0; }  //  全部断电
#endif


extern TsStepperMotor StepperMotor1;


void BSP_SteeperMotor_InitGpio(TsStepperMotor* pMotor
    , GPIO_TypeDef *port, uint16_t pin, TeMotorGpioLine linex);
void BSP_MotorBeat(TsStepperMotor* pMotor, TeMotorBeat beat);

void BSP_SteeperMotor_Init(void);






#endif //!__STEPPER_kMotorH__

