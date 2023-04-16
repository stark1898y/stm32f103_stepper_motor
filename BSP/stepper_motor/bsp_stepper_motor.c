#include "bsp_stepper_motor.h"
#include "elog.h"

#define LOG_TAG "motor"

TsStepperMotor StepperMotor1;

// uint8_t beat = 0000 0 0 0 1;
// D C B A
// & 0x01 0x02 04 08
// 顺时针
const uint8_t beat_table_cw[8] = {0x01, 0x03, 0x02
    , 0x06, 0x04, 0x0C, 0x08, 0x09};

// const uint8_t beat_table_cw[8] = {0x08, 0x0C, 0x04, 0x06
//   , 0x02, 0x03, 0x01, 0x09};

// const uint8_t beat_table_acw[8] = {0x09, 0x01, 0x03, 0x02, 0x06
//     , 0x04, 0x0C, 0x08};

void BSP_MotorBeat(TsStepperMotor *pMotor, TeMotorBeat beat)
{
    // UNUSED(pMotor);
    #if 1
    // log_d("/************beat = %d*************/", beat);
    for (uint8_t i = kLineA; i <= kLineD; i++)
    {
        HAL_GPIO_WritePin(pMotor->Gpio[i].port, pMotor->Gpio[i].pin
        , (GPIO_PinState)(beat_table_cw[beat] >> i & 0x01));
        // log_d("pMotor->Gpio[%d].pin = %d", i
        //     // , (GPIO_PinState)(beat_table_cw[beat] & (0x01 << i)));
        //     , (GPIO_PinState)(beat_table_cw[beat] >> i & 0x01));
    }
    // log_d("/************beat = %d*************/", beat);
    // elog_raw("\r\n");
    #endif

    // HAL_GPIO_WritePin(MOTOR_A_GPIO_Port
    //     , MOTOR_A_Pin
    //     , (GPIO_PinState)(beat_table_cw[beat] >> 0 & 0x01));

    // HAL_GPIO_WritePin(MOTOR_B_GPIO_Port
    //     , MOTOR_B_Pin
    //     , (GPIO_PinState)(beat_table_cw[beat] >> 1 & 0x01));

    // HAL_GPIO_WritePin(MOTOR_C_GPIO_Port
    //     , MOTOR_C_Pin
    //     , (GPIO_PinState)(beat_table_cw[beat] >> 2 & 0x01));

    // HAL_GPIO_WritePin(MOTOR_D_GPIO_Port
    //     , MOTOR_D_Pin
    //     , (GPIO_PinState)(beat_table_cw[beat] >> 3 & 0x01));
}

void BSP_SteeperMotor_InitGpio(TsStepperMotor *pMotor, GPIO_TypeDef *port, uint16_t pin, TeMotorGpioLine linex)
{
    pMotor->Gpio[linex].port = port;
    pMotor->Gpio[linex].pin  = pin;
}

void BSP_SteeperMotor_Init(void)
{
    BSP_SteeperMotor_InitGpio(&StepperMotor1, MOTOR_A_GPIO_Port, MOTOR_A_Pin, kLineA);
    BSP_SteeperMotor_InitGpio(&StepperMotor1, MOTOR_B_GPIO_Port, MOTOR_B_Pin, kLineB);
    BSP_SteeperMotor_InitGpio(&StepperMotor1, MOTOR_C_GPIO_Port, MOTOR_C_Pin, kLineC);
    BSP_SteeperMotor_InitGpio(&StepperMotor1, MOTOR_D_GPIO_Port, MOTOR_D_Pin, kLineD);
}
