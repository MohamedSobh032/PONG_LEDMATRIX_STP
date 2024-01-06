/*******************************************/
/* SWC: RCC Driver                         */
/* Author: Mohamed Sobh                    */
/* Version: v0.0                           */
/* Date: 04 AUG 2023                       */
/* Description: This is the implem. of RCC */
/*******************************************/
/* File Guard */
#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H
/* RCC: AHB1, Base Address: 0x40023800 */

#define RCC_CR                   *((volatile u32*) 0x40023800)
#define RCC_PLLCFGR              *((volatile u32*) 0x40023804)
#define RCC_CFGR                 *((volatile u32*) 0x40023808)
#define RCC_AHB1ENR              *((volatile u32*) 0x40023830)
#define RCC_AHB2ENR              *((volatile u32*) 0x40023834)
#define RCC_APB1ENR              *((volatile u32*) 0x40023840)
#define RCC_APB2ENR              *((volatile u32*) 0x40023844)


/* Private Macros */

#define HSI                    0 
#define HSE                    1
#define PLL                    2

/* Bits Configuration */
    /* RCC_CR */
#define HSION                  0
#define HSEON                  16
#define PLLON                  24

    /* RCC_CFGR */
#define SW0                    0
#define SW1                    1


#define NOTBYPASSED            0
#define BYPASSED               1

#endif