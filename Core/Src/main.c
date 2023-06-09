/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bsp_uart.h"
#include "bsp_soft_timer.h"
#include "elog.h"
#include "bsp_stepper_motor.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define LOG_TAG    "main"

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
static void test_elog(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void test_elog(void)
{
    /* test log output for all level */
    log_a("log_a: Hello EasyLogger!");
    log_e("log_e: Hello EasyLogger!");
    log_w("log_w: Hello EasyLogger!");
    log_i("log_i: Hello EasyLogger!");
    log_d("log_d: Hello EasyLogger!");
    log_v("log_v: Hello EasyLogger!");
    elog_raw("elog_raw: Hello EasyLogger!\r\n");
}

/*
* 函数名称：Easylogger_Init
* 输入参数：None
* �? �? 值：None
* �?    者：Barry
* 功能描述：初始化Easylogger打印，配置log输出的颜色�?�字体�?�输出内容等
* 修改记录：None
*/
void Easylogger_Init(void)
{
  /* 初始化Easylogger */
  elog_init();

  /* 使能颜色输出 */
  elog_set_text_color_enabled(true);

  /* 输出�?有内�? */
  elog_set_fmt(ELOG_LVL_ASSERT, ELOG_FMT_ALL);

  /* 输出日志级别信息和日志TAG */
  elog_set_fmt(ELOG_LVL_ERROR, ELOG_FMT_LVL | ELOG_FMT_TAG);
  elog_set_fmt(ELOG_LVL_WARN, ELOG_FMT_LVL | ELOG_FMT_TAG);
  elog_set_fmt(ELOG_LVL_INFO, ELOG_FMT_LVL | ELOG_FMT_TAG);

  /* 除了时间、进程信息�?�线程信息之外，其余全部输出 */
  elog_set_fmt(ELOG_LVL_DEBUG, ELOG_FMT_ALL & ~(ELOG_FMT_TIME | ELOG_FMT_P_INFO | ELOG_FMT_T_INFO));

  /* 输出�?有内�? */
  elog_set_fmt(ELOG_LVL_VERBOSE, ELOG_FMT_ALL);

  /* 启动Easylogger */
  elog_start();
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  BSP_SoftTimer_Init();
  BSP_UART_Init();
  Easylogger_Init();

  BSP_SteeperMotor_Init();

  BSP_SteeperMotor_Start(&StepperMotor1, 2
    , kMotorDirCw, kMotorModeStep, 4096);

  BSP_SteeperMotor_Start(&StepperMotor2, 2
    , kMotorDirAcw, kMotorModeLoop, 4096);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    // for (uint8_t i = kBeatDa; i >= kBeatA; i--)
    // for (int8_t i = kBeatDa; i >= kBeatA; i--)
    // for (int8_t i = 0; i <= 7; i++)
    // {

    //   BSP_MotorBeat(&StepperMotor1, (uint8_t)i);
    //   HAL_Delay(10);
      // BSP_MotorBeat(&StepperMotor1, kBeatAb);
      // HAL_Delay(10);
      // BSP_MotorBeat(&StepperMotor1, kBeatB);
      // HAL_Delay(10);
      // BSP_MotorBeat(&StepperMotor1, kBeatBc);
      // HAL_Delay(10);
      // BSP_MotorBeat(&StepperMotor1, kBeatC);
      // HAL_Delay(10);
      // BSP_MotorBeat(&StepperMotor1, kBeatCd);
      // HAL_Delay(10);
      // BSP_MotorBeat(&StepperMotor1, kBeatD);
      // HAL_Delay(10);
      // BSP_MotorBeat(&StepperMotor1, kBeatDa);
      // HAL_Delay(10);

    // }
    // StepperMotorAction(&StepperMotor1);
    // BSP_SteeperMotor_Loop();
    // HAL_Delay(1);
    BSP_SoftTimer_Loop();
    // StepperMotorAction(&StepperMotor1);
    // HAL_Delay(1);


    // test_elog();
    // printf("123\r\n");
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
