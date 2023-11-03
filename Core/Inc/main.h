/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

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
#define RTD5_IN1_Pin GPIO_PIN_0
#define RTD5_IN1_GPIO_Port GPIOC
#define RTD6_IN2_Pin GPIO_PIN_1
#define RTD6_IN2_GPIO_Port GPIOC
#define SD_SPI2_MISO_Pin GPIO_PIN_2
#define SD_SPI2_MISO_GPIO_Port GPIOC
#define Buzzer_Pin GPIO_PIN_0
#define Buzzer_GPIO_Port GPIOA
#define RTD1_IN6_Pin GPIO_PIN_1
#define RTD1_IN6_GPIO_Port GPIOA
#define RTD2_IN7_Pin GPIO_PIN_2
#define RTD2_IN7_GPIO_Port GPIOA
#define TFT_CS_Pin GPIO_PIN_4
#define TFT_CS_GPIO_Port GPIOA
#define FLASH_SPI1_MISO_Pin GPIO_PIN_6
#define FLASH_SPI1_MISO_GPIO_Port GPIOA
#define FLASH_SPI1_MOSI_Pin GPIO_PIN_7
#define FLASH_SPI1_MOSI_GPIO_Port GPIOA
#define RTD3_IN13_Pin GPIO_PIN_4
#define RTD3_IN13_GPIO_Port GPIOC
#define RTD4_IN14_Pin GPIO_PIN_5
#define RTD4_IN14_GPIO_Port GPIOC
#define BTN_ENTER_Pin GPIO_PIN_9
#define BTN_ENTER_GPIO_Port GPIOE
#define BTN_DOWN_Pin GPIO_PIN_10
#define BTN_DOWN_GPIO_Port GPIOE
#define BTN_UP_Pin GPIO_PIN_11
#define BTN_UP_GPIO_Port GPIOE
#define FLASH_CS_Pin GPIO_PIN_12
#define FLASH_CS_GPIO_Port GPIOE
#define FLASH_SPI1_SCK_Pin GPIO_PIN_13
#define FLASH_SPI1_SCK_GPIO_Port GPIOE
#define DS1307_I2C2_SCL_Pin GPIO_PIN_10
#define DS1307_I2C2_SCL_GPIO_Port GPIOB
#define DS1307_I2C2_SDA_Pin GPIO_PIN_11
#define DS1307_I2C2_SDA_GPIO_Port GPIOB
#define SD_CS_Pin GPIO_PIN_12
#define SD_CS_GPIO_Port GPIOB
#define SD_SPI2_SCK_Pin GPIO_PIN_13
#define SD_SPI2_SCK_GPIO_Port GPIOB
#define SD_SPI2_MOSI_Pin GPIO_PIN_15
#define SD_SPI2_MOSI_GPIO_Port GPIOB
#define CMPRSR_SPD_Pin GPIO_PIN_9
#define CMPRSR_SPD_GPIO_Port GPIOD
#define CMPRSR_EN_Pin GPIO_PIN_10
#define CMPRSR_EN_GPIO_Port GPIOD
#define CMPRSR_FAN_GND_Pin GPIO_PIN_11
#define CMPRSR_FAN_GND_GPIO_Port GPIOD
#define CMPRSR_FAN_VCC_Pin GPIO_PIN_12
#define CMPRSR_FAN_VCC_GPIO_Port GPIOD
#define CMPRSR_D_Pin GPIO_PIN_13
#define CMPRSR_D_GPIO_Port GPIOD
#define CHRG_OK_Pin GPIO_PIN_14
#define CHRG_OK_GPIO_Port GPIOD
#define LED_Pin GPIO_PIN_15
#define LED_GPIO_Port GPIOD
#define TFT_RST_Pin GPIO_PIN_7
#define TFT_RST_GPIO_Port GPIOC
#define TFT_BKLIGHT_Pin GPIO_PIN_8
#define TFT_BKLIGHT_GPIO_Port GPIOC
#define TFT_DC_Pin GPIO_PIN_9
#define TFT_DC_GPIO_Port GPIOC
#define FLASH_RST_Pin GPIO_PIN_8
#define FLASH_RST_GPIO_Port GPIOA
#define TFT_SPI3_SCK_Pin GPIO_PIN_10
#define TFT_SPI3_SCK_GPIO_Port GPIOC
#define TFT_SPI3_MISO_Pin GPIO_PIN_11
#define TFT_SPI3_MISO_GPIO_Port GPIOC
#define TFT_SPI3_MOSI_Pin GPIO_PIN_12
#define TFT_SPI3_MOSI_GPIO_Port GPIOC
#define HTR_CTL_Pin GPIO_PIN_5
#define HTR_CTL_GPIO_Port GPIOD
#define FAN_CTL1_Pin GPIO_PIN_6
#define FAN_CTL1_GPIO_Port GPIOD
#define FAN_CTL2_Pin GPIO_PIN_7
#define FAN_CTL2_GPIO_Port GPIOD
#define EXT_I2C1_SCL_Pin GPIO_PIN_6
#define EXT_I2C1_SCL_GPIO_Port GPIOB
#define EXT_I2C1_SDA_Pin GPIO_PIN_7
#define EXT_I2C1_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
