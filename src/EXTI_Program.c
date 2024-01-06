/**********************************************/
/* SWC: EXTI Driver                           */
/* Author: Mohamed Sobh                       */
/* Version: v0.0                              */
/* Date: 4 SEPT 2023                          */
/* Description: This is the implem. of EXTI   */
/**********************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_Interface.h"
#include "EXTI_Private.h"
#include "EXTI_Config.h"

#include "GPIO_Interface.h"
#include "RCC_Interface.h"
#include "NVIC_Interface.h"

/* Global Pointer to Function for EXTI0 */
void (*GpF_EXTI0)(void) = NULL;
void (*GpF_EXTI1)(void) = NULL;

/*************************************/
/* Func. Name: EXTI_voidInit         */
/* i/p arguments: Nothing            */
/* o/p arguments: nothing            */
/* Desc. : This API Initializes EXTI */
/*************************************/
void EXTI_voidInit()
{ RCC_voidEnablePerClk(APB2, SYSCFGEN); }

/*************************************************/
/* Func. Name: EXTI_voidSetEXTILineEnable        */
/* i/p arguments: Copy_u8LineId: LINE0 -> LINE15 */
/* o/p arguments: nothing                        */
/* Desc. : This API Enables a specific Line EXTI */
/*************************************************/
void EXTI_voidSetEXTILineEnable(u8 Copy_u8LineId)
{ 
    if (Copy_u8LineId > LINE15)
    { /* Do Nothing */ }
    else
    {
        SET_BIT(EXTI_IMR, Copy_u8LineId);
        if (Copy_u8LineId < LINE5)
        { NVIC_voidEnablePeriInt(Copy_u8LineId + 6); }
        else if (Copy_u8LineId < LINE10)
        { NVIC_voidEnablePeriInt(23); }
        else
        { NVIC_voidEnablePeriInt(40); }
    }
}

/**************************************************/
/* Func. Name: EXTI_voidSetEXTILineDisable        */
/* i/p arguments: Copy_u8LineId: LINE0 -> LINE15  */
/* o/p arguments: nothing                         */
/* Desc. : This API Disables a specific Line EXTI */
/**************************************************/
void EXTI_voidSetEXTILineDisable(u8 Copy_u8LineId)
{ 
    if (Copy_u8LineId > LINE15)
    { /* Do Nothing */ }
    else
    {
        CLR_BIT(EXTI_IMR, Copy_u8LineId);
        if (Copy_u8LineId < LINE5)
        { NVIC_voidDisablePeriInt(Copy_u8LineId + 6); }
        else if (Copy_u8LineId < LINE10)
        { NVIC_voidDisablePeriInt(23); }
        else
        { NVIC_voidDisablePeriInt(40); }
    } 
}

/****************************************************************************/
/* Func. Name: EXTI_voidSetSenseControl                                     */
/* i/p arguments: Copy_u8SenseControl: RISING_EDGE, FALLING_EDGE, ON_CHANGE */
/* i/p arguments: Copy_u8LineId: LINE0 -> LINE15                            */
/* o/p arguments: nothing                                                   */
/* Desc. : This API Sets the Sense Control of the EXTI specific Line        */
/****************************************************************************/
void EXTI_voidSetSenseControl(u8 Copy_u8SenseControl, u8 Copy_u8LineId)
{
    if ((Copy_u8SenseControl > ON_CHANGE) || (Copy_u8LineId > LINE15))
    { /* Do Nothing */ }
    else
    {
        switch (Copy_u8SenseControl)
        {
            case RISING_EDGE:   SET_BIT(EXTI_RTSR,Copy_u8LineId);
                                CLR_BIT(EXTI_FTSR,Copy_u8LineId);
                                break;
            case FALLING_EDGE:  CLR_BIT(EXTI_RTSR,Copy_u8LineId);
                                SET_BIT(EXTI_FTSR,Copy_u8LineId);
                                break;
            case ON_CHANGE:     SET_BIT(EXTI_RTSR,Copy_u8LineId);
                                SET_BIT(EXTI_FTSR,Copy_u8LineId);
                                break;
        }
    }
}

/*********************************************************************/
/* Func. Name: EXTI_voidSetEXTIPinConfig                             */
/* i/p arguments: Copy_u8PortId: IOA, IOB, IOC                       */
/* i/p arguments: Copy_u8LineId: LINE0 -> LINE15                     */
/* o/p arguments: nothing                                            */
/* Desc. : This API Set which Pin will be Output for a Specific Line */
/*********************************************************************/
void EXTI_voidSetEXTIPinConfig(u8 Copy_u8PortId, u8 Copy_u8LineId)
{
    if ((Copy_u8PortId > IOC) || (Copy_u8LineId > LINE15))
    { /* Do Nothing */ }
    else
    {
    	if (Copy_u8LineId <= LINE3)
    	{
            switch (Copy_u8PortId)
            {
                case IOA:   CLR_BIT(SYSCFG_EXTICR1,Copy_u8LineId*4);
                			CLR_BIT(SYSCFG_EXTICR1,((Copy_u8LineId*4)+1));
                			CLR_BIT(SYSCFG_EXTICR1,((Copy_u8LineId*4)+2));
                			CLR_BIT(SYSCFG_EXTICR1,((Copy_u8LineId*4)+3));
                            break;
                case IOB:   SET_BIT(SYSCFG_EXTICR1,Copy_u8LineId*4);
                            CLR_BIT(SYSCFG_EXTICR1,((Copy_u8LineId*4)+1));
                            CLR_BIT(SYSCFG_EXTICR1,((Copy_u8LineId*4)+2));
                            CLR_BIT(SYSCFG_EXTICR1,((Copy_u8LineId*4)+3));
                            break;
                case IOC:   CLR_BIT(SYSCFG_EXTICR1,Copy_u8LineId*4);
                            SET_BIT(SYSCFG_EXTICR1,((Copy_u8LineId*4)+1));
                            CLR_BIT(SYSCFG_EXTICR1,((Copy_u8LineId*4)+2));
                            CLR_BIT(SYSCFG_EXTICR1,((Copy_u8LineId*4)+3));
                            break;
            }
    	}
    	else if (Copy_u8LineId <= LINE7)
    	{
            switch (Copy_u8PortId)
            {
                case IOA:   CLR_BIT(SYSCFG_EXTICR1,((Copy_u8LineId-4)*4));
                			CLR_BIT(SYSCFG_EXTICR1,(((Copy_u8LineId-4)*4)+1));
                			CLR_BIT(SYSCFG_EXTICR1,(((Copy_u8LineId-4)*4)+2));
                			CLR_BIT(SYSCFG_EXTICR1,(((Copy_u8LineId-4)*4)+3));
                            break;
                case IOB:   SET_BIT(SYSCFG_EXTICR1,((Copy_u8LineId-4)*4));
    						CLR_BIT(SYSCFG_EXTICR1,(((Copy_u8LineId-4)*4)+1));
    						CLR_BIT(SYSCFG_EXTICR1,(((Copy_u8LineId-4)*4)+2));
    						CLR_BIT(SYSCFG_EXTICR1,(((Copy_u8LineId-4)*4)+3));
                            break;
                case IOC:	CLR_BIT(SYSCFG_EXTICR1,((Copy_u8LineId-4)*4));
							SET_BIT(SYSCFG_EXTICR1,(((Copy_u8LineId-4)*4)+1));
							CLR_BIT(SYSCFG_EXTICR1,(((Copy_u8LineId-4)*4)+2));
							CLR_BIT(SYSCFG_EXTICR1,(((Copy_u8LineId-4)*4)+3));
                            break;
            }
    	}
    	else if (Copy_u8LineId <= LINE11)
    	{
            switch (Copy_u8PortId)
            {
                case IOA:   CLR_BIT(SYSCFG_EXTICR1,((Copy_u8LineId-8)*4));
                			CLR_BIT(SYSCFG_EXTICR1,(((Copy_u8LineId-8)*4)+1));
                			CLR_BIT(SYSCFG_EXTICR1,(((Copy_u8LineId-8)*4)+2));
                			CLR_BIT(SYSCFG_EXTICR1,(((Copy_u8LineId-8)*4)+3));
                            break;
                case IOB:   SET_BIT(SYSCFG_EXTICR1,((Copy_u8LineId-8)*4));
    						CLR_BIT(SYSCFG_EXTICR1,(((Copy_u8LineId-8)*4)+1));
    						CLR_BIT(SYSCFG_EXTICR1,(((Copy_u8LineId-8)*4)+2));
    						CLR_BIT(SYSCFG_EXTICR1,(((Copy_u8LineId-8)*4)+3));
                            break;
                case IOC:	CLR_BIT(SYSCFG_EXTICR1,((Copy_u8LineId-8)*4));
							SET_BIT(SYSCFG_EXTICR1,(((Copy_u8LineId-8)*4)+1));
							CLR_BIT(SYSCFG_EXTICR1,(((Copy_u8LineId-8)*4)+2));
							CLR_BIT(SYSCFG_EXTICR1,(((Copy_u8LineId-8)*4)+3));
                            break;
            }
    	}
    	else
    	{
            switch (Copy_u8PortId)
            {
                case IOA:   CLR_BIT(SYSCFG_EXTICR1,((Copy_u8LineId-12)*4));
                			CLR_BIT(SYSCFG_EXTICR1,(((Copy_u8LineId-12)*4)+1));
                			CLR_BIT(SYSCFG_EXTICR1,(((Copy_u8LineId-12)*4)+2));
                			CLR_BIT(SYSCFG_EXTICR1,(((Copy_u8LineId-12)*4)+3));
                            break;
                case IOB:   SET_BIT(SYSCFG_EXTICR1,((Copy_u8LineId-12)*4));
    						CLR_BIT(SYSCFG_EXTICR1,(((Copy_u8LineId-12)*4)+1));
    						CLR_BIT(SYSCFG_EXTICR1,(((Copy_u8LineId-12)*4)+2));
    						CLR_BIT(SYSCFG_EXTICR1,(((Copy_u8LineId-12)*4)+3));
                            break;
                case IOC:	CLR_BIT(SYSCFG_EXTICR1,((Copy_u8LineId-12)*4));
							SET_BIT(SYSCFG_EXTICR1,(((Copy_u8LineId-12)*4)+1));
							CLR_BIT(SYSCFG_EXTICR1,(((Copy_u8LineId-12)*4)+2));
							CLR_BIT(SYSCFG_EXTICR1,(((Copy_u8LineId-12)*4)+3));
                            break;
            }
    	}
    }
}

/*******************************************************************/
/* Func. Name: EXTI_voidSetCallBack                                */
/* i/p arguments: LpF: A pointer to function                       */
/* i/p arguments: Copy_u8LineId: LINE0 -> LINE15                   */
/* o/p arguments: nothing                                          */
/* Desc. : This API Sets the function that the Handler will call   */
/*******************************************************************/
void EXTI_voidSetCallBack(void (*LpF)(void), u8 Copy_u8LineId)
{
	if (Copy_u8LineId == LINE0)
	{ GpF_EXTI0 = LpF; }
	else if (Copy_u8LineId == LINE1)
	{ GpF_EXTI1 = LpF; }
}


void EXTI0_IRQHandler(void)
{
    if (GpF_EXTI0 != NULL)
    { GpF_EXTI0(); }
    SET_BIT(EXTI_PR,0);
}

void EXTI1_IRQHandler(void)
{
    if (GpF_EXTI1 != NULL)
    { GpF_EXTI1(); }
    SET_BIT(EXTI_PR,1);
}
