/*
 * @Author       : yzy
 * @Date         : 2023-04-13 21:47:09
 * @LastEditors  : yzy
 * @LastEditTime : 2023-04-13 21:50:28
 * @FilePath     : \stm32f103_uart2_us100\BSP\soft_timer\bsp_soft_timer.h
 * @Description  :
 *
 * Copyright (c) 2023 by yzy, All Rights Reserved.
 */
#ifndef __BSP_SOFT_TIMER_H__
#define __BSP_SOFT_TIMER_H__

#include "bsp_sys.h"
#include "MultiTimer.h"

//
extern uint64_t soft_timer_ticks;

void BSP_SoftTimer_Init(void);
#define BSP_SoftTimer_Loop()    MultiTimerYield()


#endif //!__BSP_SOFT_TIMER_H__
