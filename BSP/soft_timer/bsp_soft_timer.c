#include "bsp_soft_timer.h"

uint64_t soft_timer_ticks;

uint64_t BSP_SoftTimer_GetTicks(void)
{
    return soft_timer_ticks;
}


void BSP_SoftTimer_Init(void)
{
    MultiTimerInstall(BSP_SoftTimer_GetTicks);
}


// void BSP_SoftTimer_Loop(void)
// {
//     MultiTimerYield();
// }
