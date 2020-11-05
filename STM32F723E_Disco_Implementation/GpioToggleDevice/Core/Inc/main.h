/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TOGGLE_PIN_7_Pin GPIO_PIN_3
#define TOGGLE_PIN_7_GPIO_Port GPIOE
#define TOGGLE_PIN_3_Pin GPIO_PIN_5
#define TOGGLE_PIN_3_GPIO_Port GPIOE
#define TOGGLE_PIN_6_Pin GPIO_PIN_6
#define TOGGLE_PIN_6_GPIO_Port GPIOE
#define TOGGLE_PIN_4_Pin GPIO_PIN_3
#define TOGGLE_PIN_4_GPIO_Port GPIOH
#define VCP_TX_Pin GPIO_PIN_6
#define VCP_TX_GPIO_Port GPIOC
#define TOGGLE_PIN_1_Pin GPIO_PIN_2
#define TOGGLE_PIN_1_GPIO_Port GPIOA
#define TOGGLE_PIN_2_Pin GPIO_PIN_5
#define TOGGLE_PIN_2_GPIO_Port GPIOC
#define TOGGLE_PIN_0_Pin GPIO_PIN_3
#define TOGGLE_PIN_0_GPIO_Port GPIOA
#define TOGGLE_PIN_5_Pin GPIO_PIN_0
#define TOGGLE_PIN_5_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
