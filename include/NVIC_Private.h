/**********************************************/
/* SWC: NVIC Driver                           */
/* Author: Mohamed Sobh                       */
/* Version: v0.0                              */
/* Date: 19 AUG 2023                          */
/* Description: This is the implem. of NVIC   */
/**********************************************/
/* File Guard */
#ifndef NVIC_PRIVATE_H
#define NVIC_PRIVATE_H

/* NVIC Base address 0xE000E100 */
#define NVIC        ((volatile NVIC_t*)0xE000E100)

/* SCB Base Address 0xE000ED00 */
#define SCB_AIRCR   *((volatile u32*)0xE000ED0C)

typedef struct
{
    volatile u32 ISER[32];
    volatile u32 ICER[32];
    volatile u32 ISPR[32];
    volatile u32 ICPR[32];
    volatile u32 IABR[32];
    volatile u32  RES[32];
    volatile u8  IPR[240];
}NVIC_t;

#define G4BITS_SG0BITS  0b011
#define G3BITS_SG1BITS  0b100
#define G2BITS_SG2BITS  0b101
#define G1BITS_SG3BITS  0b110
#define G0BITS_SG4BITS  0b111

#define VECT_KEY        0x05FA000

#endif