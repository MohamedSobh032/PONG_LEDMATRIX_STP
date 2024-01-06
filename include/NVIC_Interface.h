/**********************************************/
/* SWC: NVIC Driver                           */
/* Author: Mohamed Sobh                       */
/* Version: v0.0                              */
/* Date: 19 AUG 2023                          */
/* Description: This is the implem. of NVIC   */
/**********************************************/
/* File Guard */
#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H

void NVIC_voidEnablePeriInt(u8 Copy_u8PeriId);
void NVIC_voidDisablePeriInt(u8 Copy_u8PeriId);
void NVIC_voidSetPendingFlag(u8 Copy_u8PeriId);
void NVIC_voidClearPendingFlag(u8 Copy_u8PeriId);
void NVIC_voidSetPriorityConfig(u8 Copy_u8PriorityConfig);
void NVIC_voidSetPeriIntPriority(u8 Copy_u8PeriId, u8 Copy_u8GroupId, u8 Copy_u8SubGroupId);

#define G16_SG0         0  
#define G8_SG2          1
#define G4_SG4          2
#define G2_SG8          3
#define G0_SG16         4

#endif