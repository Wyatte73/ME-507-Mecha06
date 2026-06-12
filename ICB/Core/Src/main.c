/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "LCD.h"
#include <math.h>
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim4;

/* USER CODE BEGIN PV */
uint8_t en_sd[4] = {0x34, 0x00, 0x00, 0x01};
uint8_t V_MIN[4]    = {0b00000100, 0b00000000, 0b00000000, 0b00000100};
uint8_t V_MAX[4]    = {0b00000110, 0b00000000, 0b00000000, 0b10000000};
uint8_t PR_DIV[4]   = {0b00011000, 0b00000000, 0b00100010, 0b00000000};
uint8_t A_MAX[4]    = {0b00001100, 0b00000000, 0b00000000, 0b00100000};
uint8_t V_TAR[4] = {0b00001000,0b00000000,0b00000000,0b00100000};
uint8_t ref_con[4] = {0b00010100,0b00000000,0b00000011,0b00000010};

// +128
uint8_t V_TARU_1[2] = {0b00001000, 0b00000000};
uint8_t V_TARU_2[2] = {0b00000000, 0b10000000};

// -128
uint8_t V_TARD_1[2] = {0b00001000, 0b00000000};
uint8_t V_TARD_2[2] = {0b00001111, 0b10000000};


uint8_t V_ACT_1[4] = {0b00001001,0b00000000,0b00000000,0b00000000};
uint8_t V_ACT_R[4];

uint8_t V_old;
uint8_t count = 0;

uint8_t dir = 0;

LCD_param_t LCD = {RS_GPIO_Port,RS_Pin,EN_GPIO_Port,EN_Pin,RW_GPIO_Port,RW_Pin,DB0_GPIO_Port,DB0_Pin,
		DB1_GPIO_Port,DB1_Pin,DB2_GPIO_Port,DB2_Pin,DB3_GPIO_Port,DB3_Pin,DB4_GPIO_Port,DB4_Pin,
		DB5_GPIO_Port,DB5_Pin,DB6_GPIO_Port,DB6_Pin,DB7_GPIO_Port,DB7_Pin};

char digs[5];


uint8_t test;

uint32_t loop = 0;

volatile uint32_t val1 = 0;
volatile uint32_t val2 = 0;
volatile uint32_t pulse_width = 0;
volatile uint8_t is_rising_edge = 1;
float pulse_raw;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI2_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_SPI2_Init();
  MX_TIM4_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);



  /* Set V_MIN */
  HAL_GPIO_WritePin(nCs2_GPIO_Port,nCs2_Pin,GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi2,V_MIN,4,1);
  HAL_GPIO_WritePin(nCs2_GPIO_Port,nCs2_Pin,GPIO_PIN_SET);

  /* Set V_MAX */
  HAL_GPIO_WritePin(nCs2_GPIO_Port,nCs2_Pin,GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi2,V_MAX,4,1);
  HAL_GPIO_WritePin(nCs2_GPIO_Port,nCs2_Pin,GPIO_PIN_SET);

  /* Set PULSE_DIV / RAMP_DIV */
  HAL_GPIO_WritePin(nCs2_GPIO_Port,nCs2_Pin,GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi2,PR_DIV,4,1);
  HAL_GPIO_WritePin(nCs2_GPIO_Port,nCs2_Pin,GPIO_PIN_SET);

  /* Set A_MAX */
  HAL_GPIO_WritePin(nCs2_GPIO_Port,nCs2_Pin,GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi2,A_MAX,4,1);
  HAL_GPIO_WritePin(nCs2_GPIO_Port,nCs2_Pin,GPIO_PIN_SET);

  /* Set reference switch configuration and velocity mode */
  HAL_GPIO_WritePin(nCs2_GPIO_Port,nCs2_Pin,GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi2,ref_con,4,1);
  HAL_GPIO_WritePin(nCs2_GPIO_Port,nCs2_Pin,GPIO_PIN_SET);

  /* Enable Step/Dir output */
  HAL_GPIO_WritePin(nCs2_GPIO_Port,nCs2_Pin,GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi2,en_sd,4,1);
  HAL_GPIO_WritePin(nCs2_GPIO_Port,nCs2_Pin,GPIO_PIN_SET);

  /* Set V_TARGET */
  /*
  HAL_GPIO_WritePin(nCs2_GPIO_Port,nCs2_Pin,GPIO_PIN_RESET);
  HAL_SPI_Transmit(&hspi2,V_TAR_1,2,1);
  HAL_SPI_Transmit(&hspi2,V_TAR_2,2,1);
  HAL_GPIO_WritePin(nCs2_GPIO_Port,nCs2_Pin,GPIO_PIN_SET);
  */

HAL_GPIO_WritePin(RW_GPIO_Port,RW_Pin,GPIO_PIN_SET);


  Init(LCD);
  ClearDis(LCD);
  PutChar(LCD,'D');
  PutChar(LCD,'I');
  PutChar(LCD,'S');
  PutChar(LCD,'T');
  PutChar(LCD,'A');
  PutChar(LCD,'N');
  PutChar(LCD,'C');
  PutChar(LCD,'E');
  PutChar(LCD,':');
  PutChar(LCD,'0');
  PutChar(LCD,'0');
  PutChar(LCD,'.');
  PutChar(LCD,'0');
  PutChar(LCD,'0');
  PutChar(LCD,'i');
  PutChar(LCD,'n');
  while (count < 7) {ShiftCursor(LCD,'L'); count++;}
  count = 0;

  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  pulse_raw = pulse_width * .0003 - 29;


	  int16_t velocity = (int16_t)(roundf(pulse_raw) * 10);
	  // Clamp to 12-bit signed range [-2047, 2047]
	  if (velocity >  2047) velocity =  2047;
	  if (velocity < -2047) velocity = -2047;

	  V_TAR[1] = 0x00;
	  V_TAR[2] = (velocity >> 8) & 0x0F;
	  V_TAR[3] = (uint8_t)(velocity & 0xFF);

	  if (V_TAR[3] != V_old){
	  HAL_GPIO_WritePin(nCs2_GPIO_Port,nCs2_Pin,GPIO_PIN_RESET);
	  HAL_SPI_Transmit(&hspi2,V_TAR,4,1);
	  HAL_GPIO_WritePin(nCs2_GPIO_Port,nCs2_Pin,GPIO_PIN_SET);
	  V_old = V_TAR[3];
	  }


	  if (loop % 10000 == 0){
		  test = (uint8_t)roundf(pulse_raw*100);
		  if(pulse_raw<1){
			  snprintf(digs,sizeof(digs),"%d",(int)roundf(pulse_raw * 100));
			  PutChar(LCD,'0');
			  PutChar(LCD,'0');
			  ShiftCursor(LCD,'R');
			  PutChar(LCD,digs[0]);
			  PutChar(LCD,digs[1]);
		  		  }
		  else if(pulse_raw<10){
		  	  snprintf(digs,sizeof(digs),"%d",(int)roundf(pulse_raw * 100));
		  	  PutChar(LCD,'0');
		  	  PutChar(LCD,digs[0]);
		  	  ShiftCursor(LCD,'R');
		  	  PutChar(LCD,digs[1]);
		  	  PutChar(LCD,digs[2]);
		  }

		  else{
			  snprintf(digs,5,"%d",(int)roundf(pulse_raw * 100));
			  PutChar(LCD,digs[0]);
			  PutChar(LCD,digs[1]);
			  ShiftCursor(LCD,'R');
			  PutChar(LCD,digs[2]);
			  PutChar(LCD,digs[3]);
		  }
		  	  while (count < 5) {ShiftCursor(LCD,'L'); count++;}
		  	  count=0;
	  }
	  loop++;

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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 96;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi2.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 4294967295;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 9599;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 9999;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 500;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */
  HAL_TIM_MspPostInit(&htim4);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, RS_Pin|RW_Pin|DB0_Pin|DB1_Pin
                          |DB2_Pin|DB3_Pin|DB4_Pin|LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, DB5_Pin|DB6_Pin|DB7_Pin|EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(nCs2_GPIO_Port, nCs2_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : RS_Pin RW_Pin DB0_Pin DB1_Pin
                           DB2_Pin DB3_Pin DB4_Pin LED_Pin */
  GPIO_InitStruct.Pin = RS_Pin|RW_Pin|DB0_Pin|DB1_Pin
                          |DB2_Pin|DB3_Pin|DB4_Pin|LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : DB5_Pin DB6_Pin DB7_Pin nCs2_Pin */
  GPIO_InitStruct.Pin = DB5_Pin|DB6_Pin|DB7_Pin|nCs2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : EN_Pin */
  GPIO_InitStruct.Pin = EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(EN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : DN2_Pin UP2_Pin DN1_Pin UP1_Pin */
  GPIO_InitStruct.Pin = DN2_Pin|UP2_Pin|DN1_Pin|UP1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance != TIM2) return;  // Guard: only handle TIM2

    if (is_rising_edge) {
        // Capture rising edge timestamp
        val1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);

        // Switch to falling edge
        __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1,
                                      TIM_INPUTCHANNELPOLARITY_FALLING);
        is_rising_edge = 0;

    } else {
        // Capture falling edge timestamp
        val2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);

        // Handle 32-bit timer overflow correctly
        if (val2 >= val1) {
            pulse_width = val2 - val1;
        } else {
            pulse_width = (0xFFFFFFFF - val1) + val2 + 1;
        }

        // Switch back to rising edge for next pulse
        __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1,
                                      TIM_INPUTCHANNELPOLARITY_RISING);
        is_rising_edge = 1;
    }
}

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
#ifdef USE_FULL_ASSERT
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
