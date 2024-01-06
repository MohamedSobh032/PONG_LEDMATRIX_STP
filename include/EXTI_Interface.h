/**********************************************/
/* SWC: EXTI Driver                           */
/* Author: Mohamed Sobh                       */
/* Version: v0.0                              */
/* Date: 4 SEPT 2023                          */
/* Description: This is the implem. of EXTI   */
/**********************************************/
/* File Guard */
#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

void EXTI_voidInit();
void EXTI_voidSetEXTILineEnable(u8 Copy_u8LineId);
void EXTI_voidSetEXTILineDisable(u8 Copy_u8LineId);
void EXTI_voidSetSenseControl(u8 Copy_u8SenseControl, u8 Copy_u8LineId);
void EXTI_voidSetEXTIPinConfig(u8 Copy_u8PortId, u8 Copy_u8LineId);
void EXTI_voidSetCallBack(void (*LpF)(void), u8 Copy_u8LineId);


/* Sense Control Modes */
#define RISING_EDGE     0
#define FALLING_EDGE    1
#define ON_CHANGE       2


#define LINE0           0
#define LINE1           1
#define LINE2           2
#define LINE3           3
#define LINE4           4
#define LINE5           5
#define LINE6           6
#define LINE7           7
#define LINE8           8
#define LINE9           9
#define LINE10          10
#define LINE11          11
#define LINE12          12
#define LINE13          13
#define LINE14          14
#define LINE15          15

#endif
