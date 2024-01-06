/**********************************************/
/* SWC: GPIO Driver                           */
/* Author: Mohamed Sobh                       */
/* Version: v0.0                              */
/* Date: 11 AUG 2023                          */
/* Description: This is the implem. of GPIO   */
/**********************************************/
/*File Guard*/
#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H
/* GPIOA Base Adress is 0x40020000 */
#define GPIOA       ((volatile GPIOx_t*)0x40020000)

/* GPIOB Base Adress is 0x40020400 */
#define GPIOB       ((volatile GPIOx_t*)0x40020400)

/* GPIOC Base Adress is 0x40020800 */
#define GPIOC       ((volatile GPIOx_t*)0x40020800)


typedef struct
{
    volatile u32    MODER;
    volatile u32    OTYPER;
    volatile u32    OSPEEDR;
    volatile u32    PUPDR;
    volatile u32    IDR;
    volatile u32    ODR;
    volatile u32    BSRR;
    volatile u32    LCKR;
    volatile u32    AFRL;
    volatile u32    AFRH;
}GPIOx_t;



#endif