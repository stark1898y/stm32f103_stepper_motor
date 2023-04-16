#include "bsp_stepper_motor.h"
#include "bsp_soft_timer.h"
#include "elog.h"

#define LOG_TAG "motor"

TsStepperMotor StepperMotor1;
TsStepperMotor StepperMotor2;


MultiTimer MultiTimer_StepperMotor;


uint32_t ticks;        //  定时器中的计数变量

/* StepperMotor handle list head. */
static TsStepperMotor* StepperMotorList = NULL;

// uint8_t beat = 0000 0 0 0 1;
// D C B A
// & 0x01 0x02 04 08
// 顺时针
const uint8_t beat_table_cw[9] = {0x01, 0x03, 0x02
    , 0x06, 0x04, 0x0C, 0x08, 0x09, 0x00};

void MultiTimer_StepperMotor_Cb(MultiTimer* timer, void* userData)
{
    BSP_SteeperMotor_Loop();
    MultiTimerStart(&MultiTimer_StepperMotor
        , MOTOR_TICK_TIME_MS, MultiTimer_StepperMotor_Cb, NULL);
}

void BSP_MotorBeat(TsStepperMotor *pMotor, TeMotorBeat beat)
{
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
}

void BSP_SteeperMotor_InitGpio(TsStepperMotor *pMotor, GPIO_TypeDef *port, uint16_t pin, TeMotorGpioLine linex)
{
    pMotor->Gpio[linex].port = port;
    pMotor->Gpio[linex].pin  = pin;
}

void BSP_SteeperMotor_Init(void)
{
    BSP_SteeperMotor_InitGpio(&StepperMotor1, MOTOR1_A_GPIO_Port, MOTOR1_A_Pin, kLineA);
    BSP_SteeperMotor_InitGpio(&StepperMotor1, MOTOR1_B_GPIO_Port, MOTOR1_B_Pin, kLineB);
    BSP_SteeperMotor_InitGpio(&StepperMotor1, MOTOR1_C_GPIO_Port, MOTOR1_C_Pin, kLineC);
    BSP_SteeperMotor_InitGpio(&StepperMotor1, MOTOR1_D_GPIO_Port, MOTOR1_D_Pin, kLineD);

    BSP_SteeperMotor_InitGpio(&StepperMotor2, MOTOR2_A_GPIO_Port, MOTOR2_A_Pin, kLineA);
    BSP_SteeperMotor_InitGpio(&StepperMotor2, MOTOR2_B_GPIO_Port, MOTOR2_B_Pin, kLineB);
    BSP_SteeperMotor_InitGpio(&StepperMotor2, MOTOR2_C_GPIO_Port, MOTOR2_C_Pin, kLineC);
    BSP_SteeperMotor_InitGpio(&StepperMotor2, MOTOR2_D_GPIO_Port, MOTOR2_D_Pin, kLineD);

    // MultiTimer
    MultiTimerStart(&MultiTimer_StepperMotor, MOTOR_TICK_TIME_MS, MultiTimer_StepperMotor_Cb, NULL);
}

void BSP_SteeperMotor_Start(TsStepperMotor* pMotor, uint8_t speed
    , TeMotorDirection dir, TeMotorMode mode, uint16_t step)
{
    TsStepperMotor** NextMotor = &StepperMotorList;

    /* Remove the existing target timer. */
    for (; *NextMotor; NextMotor = &(*NextMotor)->next)
    {
        if (pMotor == *NextMotor)
        {
            *NextMotor = pMotor->next; /* remove from list */
            break;
        }
    }

    /* Init timer. */
    pMotor->speed = speed;
    pMotor->dir = dir;
    pMotor->mode = mode;
    pMotor->step = step;
    pMotor->control = kMotorCtrlRun;

    /* Insert timer. */
    for (NextMotor = &StepperMotorList;; NextMotor = &(*NextMotor)->next)
    {
        if (!*NextMotor)
        {
            pMotor->next = NULL;
            *NextMotor = pMotor;
            break;
        }
        // if (timer->deadline < (*nextTimer)->deadline)
        // {
        //     timer->next = *nextTimer;
        //     *nextTimer = timer;
        //     break;
        // }
    }
}

#if 1
void BSP_SteeperMotor_Stop(TsStepperMotor* pMotor)
{
    TsStepperMotor** NextMotor = &StepperMotorList;
    /* Find and remove timer. */
    for (; *NextMotor; NextMotor = &(*NextMotor)->next)
    {
        TsStepperMotor* entry = *NextMotor;
        if (entry == pMotor)
        {
            *NextMotor = pMotor->next;
            // pMotor->mode = kMotorCtrlStop;
            break;
        }
    }
}

// void BSP_SteeperMotor_Control(TsStepperMotor *pMotor, )
// {

// }

#endif

/**
 * @description: 在定时器中2ms循环调用，步进电机处理函数
 * @param {struct} StepperMotor
 * @return {*}
 */
void StepperMotorAction(TsStepperMotor* pMotor)
{
    pMotor->ticks++;

    if(pMotor->ticks >= pMotor->speed)
    {
        pMotor->ticks = 0;

        if(pMotor->step > 0 || pMotor->mode == kMotorModeLoop)
        {
            if(pMotor->mode == kMotorModeStep)   //  步数的精准控制
            {
                pMotor->step--;
            }
            if(pMotor->control == kMotorCtrlStop)
            {
                BSP_MotorBeat(pMotor, kBeatStop);
            }

            if(pMotor->dir == kMotorDirCw)
            {
                BSP_MotorBeat(pMotor, pMotor->beat);

                if (pMotor->beat < kBeatDa)
                {
                    pMotor->beat++;
                }
                if(pMotor->beat >= kBeatDa)
                {
                    pMotor->beat = kBeatA;
                }
            }
            else if(pMotor->dir == kMotorDirAcw)
            {
                BSP_MotorBeat(pMotor, pMotor->beat);

                if(pMotor->beat > 0)
                {
                    pMotor->beat--;
                }
                else
                {
                    pMotor->beat = kBeatDa;
                }
            }
        }
        else if(pMotor->step == 0 && pMotor->mode == kMotorModeStep)//  走完了所有步数Motor->step
        // else
        {
            BSP_MotorBeat(pMotor, kBeatStop);
            pMotor->control = kMotorCtrlStop;
        }
    }
}

#if 1
void BSP_SteeperMotor_Loop(void)
{
    TsStepperMotor* entry = StepperMotorList;

    for (; entry; entry = entry->next)
    {
    //     /* Sorted list, just process with the front part. */
    //     // if (platformTicksFunction() < entry->deadline)
    //     // {
    //     //     return (int)(entry->deadline - platformTicksFunction());
    //     // }
    //     /* remove expired timer from list */
        // StepperMotorList = entry->next;

        /* call callback */
        // if (entry->callback)
        // {
        //     entry->callback(entry, entry->userData);
        // }
        StepperMotorAction(entry);
        // StepperMotorAction(&StepperMotor1);
    }
    // SteppersMotorAction(&StepperMotor1);
}
#endif
