#ifndef __BSP_US100_H__
#define __BSP_US100_H__

#include "bsp_sys.h"
#include "bsp_uart.h"

#define US100_USED_UART_MODE    1
// #define US100_USED_IO_MODE   0

#define US100_UART  huart2

extern uint16_t us100_current_mm;
extern uint8_t us100_read_ok_flag;

void BSP_US100_Init(void);
void BSP_US100_Start(void);
uint16_t BSP_US100_Read(void);
void BSP_US100_Loop(void);


#endif // !__BSP_US100_H__
