#include "bsp_uart.h"
// #include "bsp_us100.h"

uint8_t uart1_rx_buffer[UART1_RX_BUFFER_LEN];
uint8_t uart1_rx_temp_data;
uint8_t uart1_rx_cnt;
uint8_t uart1_rx_flag;

uint8_t uart2_rx_buffer[UART2_RX_BUFFER_LEN];
uint8_t uart2_rx_temp_data;
uint8_t uart2_rx_cnt;
uint8_t uart2_rx_flag;

int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
    return ch;
}

void BSP_UART_Init(void)
{
    HAL_UART_Receive_IT(&huart1, (uint8_t *)&uart1_rx_temp_data, 1);
    HAL_UART_Receive_IT(&huart2, (uint8_t *)&uart2_rx_temp_data, 1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    // printf("HAL_UART_RxCpltCallback\r\n");
    if (huart->Instance == USART1)
    {
        // HAL_UART_Transmit(&huart1, (uint8_t*)&uart1_rx_temp_data, 1, 100);
        if (uart1_rx_cnt >= 255)
        {
            uart1_rx_flag = 1;
        }
        else
        {
            uart1_rx_buffer[uart1_rx_cnt++] = uart1_rx_temp_data;
            if (uart1_rx_buffer[uart1_rx_cnt - 2] == 0x0D && uart1_rx_buffer[uart1_rx_cnt - 1] == 0x0A)
            {
                uart1_rx_flag = 1;
            }
        }
        HAL_UART_Receive_IT(&huart1, (uint8_t *)&uart1_rx_temp_data, 1);
    }
    else if (huart->Instance == USART2)
    {
        if (uart2_rx_cnt >= 255)
        {
            uart2_rx_flag = 1;
        }
        else
        {
            uart2_rx_buffer[uart2_rx_cnt++] = uart2_rx_temp_data;
            // if (uart2_rx_buffer[uart2_rx_cnt - 2] == 0x0D && uart2_rx_buffer[uart2_rx_cnt - 1] == 0x0A)
            // {
            //     uart2_rx_flag = 1;
            // }
            if (uart2_rx_cnt >= 2)
            {
                uart2_rx_flag = 1;
                // uart2_rx_cnt = 0;
            }
        }
        // HAL_UART_Transmit(&huart2, (uint8_t*)&uart2_rx_temp_data, 1, 100);
        HAL_UART_Receive_IT(&huart2, (uint8_t *)&uart2_rx_temp_data, 1);
    }
}
