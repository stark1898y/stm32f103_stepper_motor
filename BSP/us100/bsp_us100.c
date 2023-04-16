#include "bsp_us100.h"
#include "bsp_uart.h"
#include "bsp_soft_timer.h"

uint8_t us100_read_ok_flag;

uint8_t us100_timer_flag = 0;
uint16_t us100_current_mm = 0;

// uint16_t us100_current_mm;
MultiTimer Us100StartTimer;

void Us100StartTimer_Cb(MultiTimer* timer, void* userData)
{
    us100_timer_flag = 1;
}

void BSP_US100_Init(void)
{
    #if (US100_USED_UART_MODE == 1)
    //
    #elif
    //
    #endif

    BSP_US100_Start();
}

void BSP_US100_Start(void)
{
#if (US100_USED_UART_MODE == 1)
    uint8_t us100_start_sign = 0x55;
    HAL_UART_Transmit(&US100_UART, &us100_start_sign, 1, 100);
#elif
//
#endif
    MultiTimerStart(&Us100StartTimer, 1000, Us100StartTimer_Cb, NULL);

    memset(uart2_rx_buffer, 0, 10);
    uart2_rx_flag = 0;
    us100_timer_flag = 0;
}

// void BSP_US100_GetData(void)
// {

// }


uint16_t BSP_US100_Read(void)
{
    uint16_t us100_current_mm = 0;

    // HAL_Delay(1000);
    // printf("uart2_rx_cnt = %d\r\n"
    //     , uart2_rx_cnt);
    // printf("uart2_rx_buffer = 0x%X 0x%X\r\n"
    //     , uart2_rx_buffer[0], uart2_rx_buffer[1]);
    if (uart2_rx_flag == 1 || us100_timer_flag == 1)
    {
        us100_current_mm = uart2_rx_buffer[0] * 256
                    + uart2_rx_buffer[1];

        uart2_rx_flag = 0;
        memset(uart2_rx_buffer, 0, uart2_rx_cnt);
        uart2_rx_cnt = 0;

        BSP_US100_Start();
    }

    return us100_current_mm;
}

void BSP_US100_Loop(void)
{
    if (uart2_rx_flag == 1 || us100_timer_flag == 1)
    {
        us100_current_mm = uart2_rx_buffer[0] * 256
                    + uart2_rx_buffer[1];
        us100_read_ok_flag = 1;

        uart2_rx_flag = 0;
        memset(uart2_rx_buffer, 0, uart2_rx_cnt);
        uart2_rx_cnt = 0;

        BSP_US100_Start();
    }
}
