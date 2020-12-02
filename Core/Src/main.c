/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include <string.h>
#include <Sensor_TSL2561.h>
#include <bme280.h>
#include <LoRa_module/LoRa_main_file.h>
#include <GrowTimer/GrowTimer_LoRa_module.h>
#include <GrowTimer/GrowTimer_sensor.h>
//#include <LoRa_contact_data.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define BAND	43325E4
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim2;

/* Definitions for Task01 */
osThreadId_t Task01Handle;
const osThreadAttr_t Task01_attributes = {
  .name = "Task01",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for Task02 */
osThreadId_t Task02Handle;
const osThreadAttr_t Task02_attributes = {
  .name = "Task02",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for Task03 */
osThreadId_t Task03Handle;
const osThreadAttr_t Task03_attributes = {
  .name = "Task03",
  .priority = (osPriority_t) osPriorityHigh,
  .stack_size = 512 * 4
};
/* USER CODE BEGIN PV */

												// TSL2561
//typedef struct {
//	uint16_t lux;
//	uint16_t temperature;
//	uint16_t humidity;
//	uint16_t pressure;
//	uint16_t CO2;
//	uint16_t TVOC;
//} SensorsDataTypeDef;

SensorsDataTypeDef sensors_data;
LoRa_sensor illumination_sensor;

struct LoRa_module lora_module = {
		.my_adr = {0x01, 0x00, 0x01},
		.esp_adr = {0x01, 0x00, 0x00},
		.state_regist = 1,
		.num_packet = 0,
		.amt_sensors = 1,
		.sensors = &illumination_sensor};
uint8_t result;

unsigned  char time = 2;
bool gain = 0;
unsigned  int ms = 0;
// If gain = false (0), device is set to low gain (1X)
// If gain = high (1), device is set to high gain (16X)
// If time = 0, integration will be 13.7ms
// If time = 1, integration will be 101ms
// If time = 2, integration will be 402ms
// If time = 3, use manual start / stop (ms = 0)
// ms will be set to integration time
												// TSL2561
int8_t user_i2c_write(uint8_t id, uint8_t reg_addr, uint8_t *data, uint16_t len);
int8_t user_i2c_read(uint8_t id, uint8_t reg_addr, uint8_t *data, uint16_t len);
void user_delay_ms(uint32_t period);
struct bme280_dev dev = {.dev_id = BME280_I2C_ADDR_SEC, .intf = BME280_I2C_INTF, .read = user_i2c_read, .write = user_i2c_write, .delay_ms = user_delay_ms};
struct bme280_data comp_data;
int8_t rslt;
uint16_t exti5_10, exti2;
uint16_t cnt_task_1, cnt_task_2, cnt_task_3;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM2_Init(void);
void StartTask01(void *argument);
void StartTask02(void *argument);
void StartTask03(void *argument);

/* USER CODE BEGIN PFP */
void lora_module_recieve_packet(struct LoRa_module* module);
void lora_module_send_packet_read_data(struct LoRa_module* module);
void vTaskDelayUntil(TickType_t * const pxPreviousWakeTime, const TickType_t xTimeIncrement);
TickType_t xTaskGetTickCount(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int8_t user_i2c_read(uint8_t id, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
  if(HAL_I2C_Master_Transmit(&hi2c1, (id << 1), &reg_addr, 1, 10) != HAL_OK) return -1;
  if(HAL_I2C_Master_Receive(&hi2c1, (id << 1) | 0x01, data, len, 10) != HAL_OK) return -1;

  return 0;
}

void user_delay_ms(uint32_t period)
{
  HAL_Delay(period);
}

int8_t user_i2c_write(uint8_t id, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
  int8_t *buf;
  buf = malloc(len +1);
  buf[0] = reg_addr;
  memcpy(buf +1, data, len);
  if(HAL_I2C_Master_Transmit(&hi2c1, (id << 1), (uint8_t*)buf, len + 1, HAL_MAX_DELAY) != HAL_OK) return -1;
  free(buf);
  return 0;
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
//  lora_sensor_init(&dht_sensor, Air_temperature, 0);
//  lora_module = lora_module_init(&dht_sensor, 1, 0, 0, LED1_PIN_GPIO_Port, LED1_PIN_Pin,
//		  LED3_PIN_GPIO_Port, LED3_PIN_Pin, LED2_PIN_GPIO_Port, LED2_PIN_Pin);

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  LoRa_init(&hspi1);
  result = LoRa_begin(BAND, true, 14, 8, 250E3, 0x4A);
  if(result == 0) {
	  HAL_GPIO_WritePin(LED1_PIN_GPIO_Port, LED1_PIN_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LED2_PIN_GPIO_Port, LED2_PIN_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LED3_PIN_GPIO_Port, LED3_PIN_Pin, GPIO_PIN_SET);
	  HAL_Delay(500);
	  HAL_GPIO_WritePin(LED1_PIN_GPIO_Port, LED1_PIN_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(LED2_PIN_GPIO_Port, LED2_PIN_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(LED3_PIN_GPIO_Port, LED3_PIN_Pin, GPIO_PIN_RESET);
	  while(result != 0) {
		  result = LoRa_begin(BAND, true, 14, 11, 125E3, 0x4A);
			  HAL_GPIO_WritePin(LED1_PIN_GPIO_Port, LED1_PIN_Pin, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(LED2_PIN_GPIO_Port, LED2_PIN_Pin, GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(LED3_PIN_GPIO_Port, LED3_PIN_Pin, GPIO_PIN_RESET);
	  }
  }

  lora_sensor_init(&illumination_sensor, 6 , 0);

  //lora_module_introduce(&lora_module);
  unsigned  char time = 2;
  TSL2561_setTiming_ms (gain, time, & ms);
  TSL2561_setPowerUp ();

  rslt = bme280_init(&dev);

  dev.settings.osr_h = BME280_OVERSAMPLING_1X;
  dev.settings.osr_p = BME280_OVERSAMPLING_16X;
  dev.settings.osr_t = BME280_OVERSAMPLING_2X;
  dev.settings.filter = BME280_FILTER_COEFF_16;
  rslt = bme280_set_sensor_settings(BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_FILTER_SEL, &dev);
  rslt = bme280_set_sensor_mode(BME280_NORMAL_MODE, &dev);
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Task01 */
  Task01Handle = osThreadNew(StartTask01, NULL, &Task01_attributes);

  /* creation of Task02 */
  Task02Handle = osThreadNew(StartTask02, NULL, &Task02_attributes);

  /* creation of Task03 */
  Task03Handle = osThreadNew(StartTask03, NULL, &Task03_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

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

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 72;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
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
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LORA_NSS_Pin|LED1_PIN_Pin|LED3_PIN_Pin|LED2_PIN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LORA_RESET_Pin|CO2_WAKE_UP_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LORA_NSS_Pin LED1_PIN_Pin LED3_PIN_Pin LED2_PIN_Pin */
  GPIO_InitStruct.Pin = LORA_NSS_Pin|LED1_PIN_Pin|LED3_PIN_Pin|LED2_PIN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LORA_DIO1_Pin LORA_DIO0_Pin */
  GPIO_InitStruct.Pin = LORA_DIO1_Pin|LORA_DIO0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LORA_RESET_Pin CO2_WAKE_UP_Pin */
  GPIO_InitStruct.Pin = LORA_RESET_Pin|CO2_WAKE_UP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI2_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin== GPIO_PIN_2) {
    exti2++;
    lora_module_recieve_packet(&lora_module);
  } else if(GPIO_Pin== GPIO_PIN_10){
    exti5_10++;
    lora_module_recieve_packet(&lora_module);
  } else{
    __NOP();
  }
}
/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartTask01 */
/**
  * @brief  Function implementing the Task01 thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartTask01 */
void StartTask01(void *argument)
{
  /* USER CODE BEGIN 5 */
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = 1000;
  xLastWakeTime = xTaskGetTickCount();
  /* Infinite loop */
  for(;;)
  {
	vTaskDelayUntil(&xLastWakeTime, xFrequency);
	unsigned int data0, data1;
	if (TSL2561_getData(&data0, &data1))
	{
		double lux;
		TSL2561_getLux(gain, ms, data0, data1, &lux);
		sensors_data.lux = lux;
		lora_sensor_set_data(&illumination_sensor,(float)lux);
	}
	cnt_task_1++;
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the Task02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void *argument)
{
  /* USER CODE BEGIN StartTask02 */
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = 2000;
  xLastWakeTime = xTaskGetTickCount();
  /* Infinite loop */
  for(;;)
  {
	vTaskDelayUntil(&xLastWakeTime, xFrequency);
	//rslt = bme280_set_sensor_mode(BME280_NORMAL_MODE, &dev);
	//dev.delay_ms(40);
	rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, &dev);
	if(rslt == BME280_OK)
	{
		sensors_data.temperature = comp_data.temperature / 100.0;      /* C  */
		sensors_data.humidity = comp_data.humidity / 1024.0;           /* %   */
		sensors_data.pressure = comp_data.pressure / 10000.0 / 1.333;  /* hPa or mmhg */
	}
	cnt_task_2++;
	//rslt = bme280_set_sensor_mode(BME280_SLEEP_MODE, &dev);
  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the Task03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void *argument)
{
  /* USER CODE BEGIN StartTask03 */
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = 5500;
  xLastWakeTime = xTaskGetTickCount();
  /* Infinite loop */
  for(;;)
  {
	vTaskDelayUntil(&xLastWakeTime, xFrequency);
	//lora_module_introduce(&lora_module, &sensors_data);
	HAL_GPIO_TogglePin(LED1_PIN_GPIO_Port, LED1_PIN_Pin);
	lora_module_send_packet_read_data(&lora_module);
	//
	HAL_GPIO_TogglePin(LORA_DIO0_GPIO_Port, LORA_DIO0_Pin);
	HAL_GPIO_TogglePin(LORA_DIO1_GPIO_Port, LORA_DIO1_Pin);
	cnt_task_3++;
	//lora_module_recieve_packet(&lora_module);
  }

  /* USER CODE END StartTask03 */
}

 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM4 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM4) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
