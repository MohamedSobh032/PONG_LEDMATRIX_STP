/********************************************/
/* SWC: STK Driver                          */
/* Author: Mohamed Sobh                     */
/* Version: v0.0                            */
/* Date: 12 AUG 2023                        */
/* Description: This is the implem. of STK  */
/********************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "STK_Interface.h"
#include "STK_Private.h"
#include "STK_Config.h"

/* Global Pointer to Function */
void (*GpF)(void) = NULL;
/* Global Variable for Interval Mode */
u8 Global_u8ModeOfInterval = 0;

/******************************************************************/
/* Func. Name: STK_voidInit                                       */
/* i/p arguments: nothing                                         */
/* o/p arguments: nothing                                         */
/* Desc. : This API allows user to Initialize the SysTick         */
/******************************************************************/
void STK_voidInit()
{
    /* 1-Disable Systick */
    CLR_BIT(STK_CTRL,0);
    /* 2-Disable Systick INT */
    CLR_BIT(STK_CTRL,1);
    /* 3-Select SysTick Clk Source */
    #if STK_CLK_SRC == AHB_DIV_BY_8
        CLR_BIT(STK_CTRL,2);
    #elif STK_CLK_SRC == AHB
        SET_BIT(STK_CTRL,2);
    #else
        #warning "Invalid Option"
    #endif
}

/******************************************************************/
/* Func. Name: STK_voidSetBusyWait                                */
/* i/p arguments: Copy_u32Ticks:                                  */
/* o/p arguments: nothing                                         */
/* Desc. : This API allows to make delay using SysTick Timer      */
/******************************************************************/
void STK_voidSetBusyWait(u32 Copy_u32Ticks)
{
    /* 1-Reload the value in the load register */
    STK_LOAD = Copy_u32Ticks;
    /* 2-Start Timer */
    SET_BIT(STK_CTRL,0);
    /* 3-Wait untill the flag is raised */
    while(!GET_BIT(STK_CTRL,16)){;}
    /* 4-Stop the Timer */
    CLR_BIT(STK_CTRL,0);
    STK_LOAD = 0;
    STK_VAL = 0;
}

/******************************************************************************/
/* Func. Name: STK_voidSetIntervalSingle                                      */
/* i/p arguments: Copy_u32Ticks                                               */
/* i/p arguments: LpF                                                         */
/* o/p arguments: nothing                                                     */
/* Desc. : This API allows to call a function for a single time using SysTick */
/******************************************************************************/
void STK_voidSetIntervalSingle(u32 Copy_u32Ticks, void (*LpF)(void))
{
    /* 1- Restart Timer */
    STK_LOAD = 0;
    STK_VAL = 0;
    /* 2- Reload the value in the load register */
    STK_LOAD = Copy_u32Ticks;
    /* 3- Start Timer */
    SET_BIT(STK_CTRL,0);
    /* 4- Save Callback */
    GpF = LpF;
    /* 5- Set mode of Interval */
    Global_u8ModeOfInterval = SINGLE_INTERVAL_MODE;
    /* 6- Enable SysTick INT */
    SET_BIT(STK_CTRL,1);
}

/*********************************************************************************/
/* Func. Name: STK_voidSetIntervalPeriodic                                       */
/* i/p arguments: u32 Copy_u32Ticks                                              */
/* i/p arguments: LpF                                                            */
/* o/p arguments: nothing                                                        */
/* Desc. : This API allows to keep calling a function periodically using SysTick */
/*********************************************************************************/
void STK_voidSetIntervalPeriodic(u32 Copy_u32Ticks, void (*LpF)(void))
{
    /* 1-Reload the value in the load register */
    STK_LOAD = Copy_u32Ticks;
    /* 2-Start Timer */
    SET_BIT(STK_CTRL,0);
    /* 3-Save Callback */
    GpF = LpF;
    /* 4- Set mode of Interval */
    Global_u8ModeOfInterval = PERIODIC_INTERVAL_MODE;
    /* 5-Enable SysTick INT */
    SET_BIT(STK_CTRL,1);
}

/*******************************************************************/
/* Func. Name: STK_u32GetElapsedTime                               */
/* i/p arguments: Nothing                                          */
/* o/p arguments: STK_LOAD - STK_VAL                               */
/* Desc. : This API allows to return the Elapsed Time              */
/*******************************************************************/
u32 STK_u32GetElapsedTime(void)
{ return (STK_LOAD - STK_VAL); }

/*******************************************************************/
/* Func. Name: STK_u32GetRemainingTime                             */
/* i/p arguments: nothing                                          */
/* o/p arguments: STK_VAL                                          */
/* Desc. : This API allows to return the Remaining Time            */
/*******************************************************************/
u32 STK_u32GetRemainingTime(void)
{ return STK_VAL; }

/*******************************************************************/
/* Func. Name: SysTick_Handler                                     */
/* i/p arguments: nothing                                          */
/* o/p arguments: nothing                                          */
/* Desc. : This API is SysTick Interrupt                           */
/*******************************************************************/
void SysTick_Handler()
{
    u8 Local_u8Temp;
    if (Global_u8ModeOfInterval == SINGLE_INTERVAL_MODE)
    {
        /* Disable INT */
        CLR_BIT(STK_CTRL,1);
        /* Stop the Timer */
        CLR_BIT(STK_CTRL,0);
        STK_LOAD = 0;
        STK_VAL = 0;
    }
    if (GpF != NULL)
    { GpF(); }
    /* Clear Flag */
    Local_u8Temp = GET_BIT(STK_CTRL,16);
}
