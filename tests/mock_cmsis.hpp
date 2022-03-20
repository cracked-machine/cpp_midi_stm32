/**
  ******************************************************************************
  * @file    mock.cmsis.hpp
  * @author  MCD Application Team
  * @brief   Mock CMSIS Cortex-M0+ Device System Source File for STM32G0xx devices.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics. 
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Apache License, Version 2.0,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/Apache-2.0
  *
  ******************************************************************************
  */

#ifndef __MOCK_CMSIS_HPP__
#define __MOCK_CMSIS_HPP__

#define __IO volatile
#include <stdint.h>

typedef struct
{
  __IO uint32_t CR1;         /*!< USART Control register 1,                 Address offset: 0x00  */
  __IO uint32_t CR2;         /*!< USART Control register 2,                 Address offset: 0x04  */
  __IO uint32_t CR3;         /*!< USART Control register 3,                 Address offset: 0x08  */
  __IO uint32_t BRR;         /*!< USART Baud rate register,                 Address offset: 0x0C  */
  __IO uint32_t GTPR;        /*!< USART Guard time and prescaler register,  Address offset: 0x10  */
  __IO uint32_t RTOR;        /*!< USART Receiver Time Out register,         Address offset: 0x14  */
  __IO uint32_t RQR;         /*!< USART Request register,                   Address offset: 0x18  */
  __IO uint32_t ISR;         /*!< USART Interrupt and status register,      Address offset: 0x1C  */
  __IO uint32_t ICR;         /*!< USART Interrupt flag Clear register,      Address offset: 0x20  */
  __IO uint32_t RDR;         /*!< USART Receive Data register,              Address offset: 0x24  */
  __IO uint32_t TDR;         /*!< USART Transmit Data register,             Address offset: 0x28  */
  __IO uint32_t PRESC;       /*!< USART Prescaler register,                 Address offset: 0x2C  */
} USART_TypeDef;

#endif 