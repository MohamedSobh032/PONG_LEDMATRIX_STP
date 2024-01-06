/*******************************************/
/* SWC: STK Driver                         */
/* Author: Mohamed Sobh                    */
/* Version: v0.0                           */
/* Date: 12 AUG 2023                       */
/* Description: This is the implem. of STK */
/*******************************************/
/* File Guard */
#ifndef STK_PRIVATE_H
#define STK_PRIVATE_H

#define STK_CTRL                    *((volatile u32*)0xE000E010)
#define STK_LOAD                    *((volatile u32*)0xE000E014)
#define STK_VAL                     *((volatile u32*)0xE000E018)
#define STK_CALIB                   *((volatile u32*)0xE000E0C0)

#define AHB_DIV_BY_8                0
#define AHB                         1

#define SINGLE_INTERVAL_MODE        0
#define PERIODIC_INTERVAL_MODE      1

#endif