/*
 * @Author       : yzy
 * @Date         : 2023-04-13 20:46:44
 * @LastEditors  : yzy
 * @LastEditTime : 2023-04-13 20:46:44
 * @FilePath     : \stm32f103_uart2_us100\BSP\uart\bsp_uart.h
 * @Description  :
 *
 * Copyright (c) 2023 by yzy, All Rights Reserved.
 */
#ifndef __BSP_UART_H__
#define __BSP_UART_H__

#include "bsp_sys.h"
#include "usart.h"

#define UART1_RX_BUFFER_LEN     (256U)
#define UART2_RX_BUFFER_LEN     (256U)

extern uint8_t uart1_rx_buffer[UART1_RX_BUFFER_LEN];
// uint8_t uart1_rx_temp_data;
extern uint8_t uart1_rx_cnt;
extern uint8_t uart1_rx_flag;

extern uint8_t uart2_rx_buffer[UART2_RX_BUFFER_LEN];
// uint8_t uart2_rx_temp_data;
extern uint8_t uart2_rx_cnt;
extern uint8_t uart2_rx_flag;

void BSP_UART_Init(void);







#endif // !__BSP_UART_H__





