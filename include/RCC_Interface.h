/********************************************/
/* SWC: RCC Driver                          */
/* Author: Mohamed Sobh                     */
/* Version: v0.0                            */
/* Date: 04 AUG 2023                        */
/* Description: This is the implem. of RCC  */
/********************************************/
/* File Guard */
#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

void RCC_voidInitSysClk(void);
void RCC_voidEnablePerClk(u8 Copy_u8BusId, u8 Copy_u8PerId);
void RCC_voidDisablePerClk(u8 Copy_u8BusId, u8 Copy_u8PerId);

#define AHB1        0
#define AHB2        1
#define APB1        2
#define APB2        3


/* AHB1 Enable Peripherals */
#define GPIOAEN     0
#define GPIOBEN     1
#define GPIOCEN     2
#define CRCEN       12
#define DMA1EN      21
#define DMA2EN      22

/* AHB2 Enable Peripherals */
#define OTGFSEN     7

/* APB1 Enable Peripherals */
#define TIM2EN      0
#define TIM3EN      1
#define TIM4EN      2
#define TIM5EN      3
#define WWDGEN      11
#define SPI2EN      14
#define SPI3EN      15
#define USART2EN    17
#define I2C1EN      21
#define I2C2EN      22
#define I2C3EN      23
#define PWREN       28

/* APB2 Enable Peripherals */
#define TIM1EN      0
#define USART1EN    4
#define USART6EN    5
#define ADC1EN      8
#define SDIOEN      11
#define SPI1EN      12
#define SPI4EN      13
#define SYSCFGEN    14
#define TIM9EN      16
#define TIM10EN     17
#define TIM11EN     18


#endif