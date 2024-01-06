/********************************************/
/* SWC: STK Driver                          */
/* Author: Mohamed Sobh                     */
/* Version: v0.0                            */
/* Date: 12 AUG 2023                        */
/* Description: This is the implem. of STK  */
/********************************************/
/* File Guard */
#ifndef STK_INTERFACE_H
#define STK_INTERFACE_H

void STK_voidInit();
void STK_voidSetBusyWait(u32 Copy_u32Ticks);
void STK_voidSetIntervalSingle(u32 Copy_u32Ticks, void (*LpF)(void));
void STK_voidSetIntervalPeriodic(u32 Copy_u32Ticks, void (*LpF)(void));
u32 STK_u32GetElapsedTime(void);
u32 STK_u32GetRemainingTime(void);

#endif