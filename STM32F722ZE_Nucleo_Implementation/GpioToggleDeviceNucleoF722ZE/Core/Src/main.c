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
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "fifo.h"
#include "commandparser.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define COMMANDLENGTH 	((uint32_t) 10000)
#define COMMANDLENGTHX2 ((uint32_t) 40000)

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
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
void ExecuteTimedSequence();
void SetPersistentState();
void Release();
void EndSends();
void SendResponse(uint8_t _command);
void PinHigh(GPIO_TypeDef* _gpioPort, uint16_t _gpioPin);
void PinLow(GPIO_TypeDef* _gpioPort, uint16_t _gpioPin);
void PinReset(GPIO_TypeDef* _gpioPort, uint16_t _gpioPin);
void SetPin(uint8_t state, GPIO_TypeDef* _gpioPort, uint16_t _gpioPin);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint8_t byte = 0;
uint8_t command = 0;
static uint8_t FifoBuffer[100];
struct Fifo g_fifo;
struct CommandParser g_commandParser;

static uint8_t pin0StateBuffer[COMMANDLENGTH];
static uint8_t pin1StateBuffer[COMMANDLENGTH];
static uint8_t pin2StateBuffer[COMMANDLENGTH];
static uint8_t pin3StateBuffer[COMMANDLENGTH];
static uint8_t pin4StateBuffer[COMMANDLENGTH];
static uint8_t pin5StateBuffer[COMMANDLENGTH];
static uint8_t pin6StateBuffer[COMMANDLENGTH];
static uint8_t pin7StateBuffer[COMMANDLENGTH];
static uint8_t timeDelayBuffer[COMMANDLENGTHX2];

struct Fifo g_pin0Fifo;
struct Fifo g_pin1Fifo;
struct Fifo g_pin2Fifo;
struct Fifo g_pin3Fifo;
struct Fifo g_pin4Fifo;
struct Fifo g_pin5Fifo;
struct Fifo g_pin6Fifo;
struct Fifo g_pin7Fifo;
struct Fifo timeDelayFifo;



enum SyncBytes
{
	SyncByte1 = 0xA5,
	SyncByte2 = 0xC3
};

enum Commands
{
	c_Connect				= 0xA1,
	c_ExecuteTimedSequence 	= 0xB1,
	c_SetPersistentState 	= 0xB2,
	c_Release 				= 0xB3,
	c_EndSends 				= 0xB4
};

enum FireType
{
	FLOAT 		= 0x0,
	LOW 		= 0x1,
	HIGH 		= 0x2,
	NO_CHANGE 	= 0x3
};

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
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
  Fifo_init(&g_fifo, FifoBuffer, 100);
  CommandParser_init(&g_commandParser, &g_fifo, SyncByte1, SyncByte2);

  Fifo_init(&g_pin0Fifo, pin0StateBuffer, COMMANDLENGTH);
  Fifo_init(&g_pin1Fifo, pin1StateBuffer, COMMANDLENGTH);
  Fifo_init(&g_pin2Fifo, pin2StateBuffer, COMMANDLENGTH);
  Fifo_init(&g_pin3Fifo, pin3StateBuffer, COMMANDLENGTH);
  Fifo_init(&g_pin4Fifo, pin4StateBuffer, COMMANDLENGTH);
  Fifo_init(&g_pin5Fifo, pin5StateBuffer, COMMANDLENGTH);
  Fifo_init(&g_pin6Fifo, pin6StateBuffer, COMMANDLENGTH);
  Fifo_init(&g_pin7Fifo, pin7StateBuffer, COMMANDLENGTH);

  Fifo_init(&timeDelayFifo, timeDelayBuffer, COMMANDLENGTHX2);

  HAL_UART_Receive_IT(&huart3, &byte, 1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  HAL_Delay(10);
	  command = CommandParser_getCommand(&g_commandParser);

	  switch(command)
	  {
	  case c_Connect:
		  break;
	  case c_ExecuteTimedSequence:
		  ExecuteTimedSequence();
		  break;
	  case c_SetPersistentState:
		  SetPersistentState();
		  break;
	  case c_Release:
		  Release();
		  break;
	  case c_EndSends:
		  EndSends();
		  break;
	  default:
		  break;
	  }
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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART3;
  PeriphClkInitStruct.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == &huart3)
	{
		Fifo_push(&g_fifo, byte);
		HAL_UART_Receive_IT(&huart3, &byte, 1);
	}
}

void ExecuteTimedSequence()
{
	uint8_t byte = 0;

	Fifo_pop(&g_fifo);

	byte = Fifo_pop(&g_fifo);
	Fifo_push(&timeDelayFifo, byte);
	byte = Fifo_pop(&g_fifo);
	Fifo_push(&timeDelayFifo, byte);
	byte = Fifo_pop(&g_fifo);
	Fifo_push(&timeDelayFifo, byte);
	byte = Fifo_pop(&g_fifo);
	Fifo_push(&timeDelayFifo, byte);

	byte = Fifo_pop(&g_fifo);
	Fifo_push(&g_pin0Fifo, byte);

	byte = Fifo_pop(&g_fifo);
	Fifo_push(&g_pin1Fifo, byte);

	byte = Fifo_pop(&g_fifo);
	Fifo_push(&g_pin2Fifo, byte);

	byte = Fifo_pop(&g_fifo);
	Fifo_push(&g_pin3Fifo, byte);

	byte = Fifo_pop(&g_fifo);
	Fifo_push(&g_pin4Fifo, byte);

	byte = Fifo_pop(&g_fifo);
	Fifo_push(&g_pin5Fifo, byte);

	byte = Fifo_pop(&g_fifo);
	Fifo_push(&g_pin6Fifo, byte);

	byte = Fifo_pop(&g_fifo);
	Fifo_push(&g_pin7Fifo, byte);

	SendResponse(c_ExecuteTimedSequence);
}

void SetPersistentState()
{
	uint8_t state = 0x3;
	state = Fifo_pop(&g_fifo);
	SetPin(state, TOGGLE_PIN_0_GPIO_Port, TOGGLE_PIN_0_Pin);
	state = Fifo_pop(&g_fifo);
	SetPin(state, TOGGLE_PIN_1_GPIO_Port, TOGGLE_PIN_1_Pin);
	state = Fifo_pop(&g_fifo);
	SetPin(state, TOGGLE_PIN_2_GPIO_Port, TOGGLE_PIN_2_Pin);
	state = Fifo_pop(&g_fifo);
	SetPin(state, TOGGLE_PIN_3_GPIO_Port, TOGGLE_PIN_3_Pin);
	state = Fifo_pop(&g_fifo);
	SetPin(state, TOGGLE_PIN_4_GPIO_Port, TOGGLE_PIN_4_Pin);
	state = Fifo_pop(&g_fifo);
	SetPin(state, TOGGLE_PIN_5_GPIO_Port, TOGGLE_PIN_5_Pin);
	state = Fifo_pop(&g_fifo);
	SetPin(state, TOGGLE_PIN_6_GPIO_Port, TOGGLE_PIN_6_Pin);
	state = Fifo_pop(&g_fifo);
	SetPin(state, TOGGLE_PIN_7_GPIO_Port, TOGGLE_PIN_7_Pin);

	SendResponse(c_SetPersistentState);
}

void Release()
{
	PinReset(TOGGLE_PIN_0_GPIO_Port, TOGGLE_PIN_0_Pin);
	PinReset(TOGGLE_PIN_1_GPIO_Port, TOGGLE_PIN_1_Pin);
	PinReset(TOGGLE_PIN_2_GPIO_Port, TOGGLE_PIN_2_Pin);
	PinReset(TOGGLE_PIN_3_GPIO_Port, TOGGLE_PIN_3_Pin);
	PinReset(TOGGLE_PIN_4_GPIO_Port, TOGGLE_PIN_4_Pin);
	PinReset(TOGGLE_PIN_5_GPIO_Port, TOGGLE_PIN_5_Pin);
	PinReset(TOGGLE_PIN_6_GPIO_Port, TOGGLE_PIN_6_Pin);
	PinReset(TOGGLE_PIN_7_GPIO_Port, TOGGLE_PIN_7_Pin);

	SendResponse(c_Release);
}

void EndSends()
{
	SendResponse(c_EndSends);

	uint32_t timeDelay = 0;
	uint8_t byte1 = 0;
	uint8_t byte2 = 0;
	uint8_t byte3 = 0;
	uint8_t byte4 = 0;

	while(!Fifo_isEmpty(&timeDelayFifo))
	{
		byte1 = Fifo_pop(&timeDelayFifo);
		byte2 = Fifo_pop(&timeDelayFifo);
		byte3 = Fifo_pop(&timeDelayFifo);
		byte4 = Fifo_pop(&timeDelayFifo);
		timeDelay = (byte4 << 24) | (byte3 << 16) | (byte2 << 8) | byte1;

		byte1 = Fifo_pop(&g_pin0Fifo);
		SetPin(byte1, TOGGLE_PIN_0_GPIO_Port, TOGGLE_PIN_0_Pin);

		byte1 = Fifo_pop(&g_pin1Fifo);
		SetPin(byte1, TOGGLE_PIN_1_GPIO_Port, TOGGLE_PIN_1_Pin);

		byte1 = Fifo_pop(&g_pin2Fifo);
		SetPin(byte1, TOGGLE_PIN_2_GPIO_Port, TOGGLE_PIN_2_Pin);

		byte1 = Fifo_pop(&g_pin3Fifo);
		SetPin(byte1, TOGGLE_PIN_3_GPIO_Port, TOGGLE_PIN_3_Pin);

		byte1 = Fifo_pop(&g_pin4Fifo);
		SetPin(byte1, TOGGLE_PIN_4_GPIO_Port, TOGGLE_PIN_4_Pin);

		byte1 = Fifo_pop(&g_pin5Fifo);
		SetPin(byte1, TOGGLE_PIN_5_GPIO_Port, TOGGLE_PIN_5_Pin);

		byte1 = Fifo_pop(&g_pin6Fifo);
		SetPin(byte1, TOGGLE_PIN_6_GPIO_Port, TOGGLE_PIN_6_Pin);

		byte1 = Fifo_pop(&g_pin7Fifo);
		SetPin(byte1, TOGGLE_PIN_7_GPIO_Port, TOGGLE_PIN_7_Pin);

		HAL_Delay(timeDelay);
	}
}

void SendResponse(uint8_t _command)
{
	uint8_t response[3];
	response[0] = SyncByte1;
	response[1] = SyncByte2;
	response[2] = _command;

	HAL_UART_Transmit(&huart3, response, 3, HAL_MAX_DELAY);
}

void PinHigh(GPIO_TypeDef* _gpioPort, uint16_t _gpioPin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = _gpioPin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(_gpioPort, &GPIO_InitStruct);
	HAL_GPIO_WritePin(_gpioPort, _gpioPin, GPIO_PIN_SET);
}

void PinLow(GPIO_TypeDef* _gpioPort, uint16_t _gpioPin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = _gpioPin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(_gpioPort, &GPIO_InitStruct);
	HAL_GPIO_WritePin(_gpioPort, _gpioPin, GPIO_PIN_RESET);
}

void PinReset(GPIO_TypeDef* _gpioPort, uint16_t _gpioPin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = _gpioPin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(_gpioPort, &GPIO_InitStruct);
}

void SetPin(uint8_t state, GPIO_TypeDef* _gpioPort, uint16_t _gpioPin)
{
	switch(state)
	{
	case FLOAT:
		PinReset(_gpioPort, _gpioPin);
		break;
	case LOW:
		PinLow(_gpioPort, _gpioPin);
		break;
	case HIGH:
		PinHigh(_gpioPort, _gpioPin);
		break;
	case NO_CHANGE:
		break;
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
