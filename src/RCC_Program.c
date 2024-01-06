/********************************************/
/* SWC: RCC Driver                          */
/* Author: Mohamed Sobh                     */
/* Version: v0.0                            */
/* Date: 04 AUG 2023                        */
/* Description: This is the implem. of RCC  */
/********************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_Interface.h"
#include "RCC_Private.h"
#include "RCC_Config.h"

/***************************************/
/* Func. Name: RCC_voidInitSysClk      */
/* i/p arguments: nothing              */
/* o/p arguments: nothing              */
/* Desc. : This API allows user to     */ 
/* select the clk source of the system */
/***************************************/
void RCC_voidInitSysClk(void)
{
    #if SYS_CLK_SRC == HSI
        /* 1- Turn on HSI */
        SET_BIT(RCC_CR, HSION);

        /* 2- Select HSI as my system Clk*/
        CLR_BIT(RCC_CFGR, SW0);
        CLR_BIT(RCC_CFGR, SW1);
        /* AHB prescaled by 2 */
        SET_BIT(RCC_CFGR, 7);
    #elif SYS_CLK_SRC == HSE
        /* 1- Turn on HSE */
        SET_BIT(RCC_CR, HSEON);

        /* 2- Select HSE as my system Clk*/
        SET_BIT(RCC_CFGR, SW0);
        CLR_BIT(RCC_CFGR, SW1);

        /* 3- Select ByPass Mode */
        ///////////////////////////

    #elif SYS_CLK_SRC == PLL
        /* Assignment :( */
        /* 1- Turn on HSE */
        SET_BIT(RCC,CR, PLLON);
        /* Set PLLQ to 2 */
        SET_BIT(RCC_PLLCFGR,25);
        /* HSI Clock Selected on PLL */
        CLR_BIT(RCC_PLLCFGR, 22);
        /* Setting PLLP to 2 */
        CLR_BIT(RCC_PLLCFGR, 16);
        CLR_BIT(RCC_PLLCFGR, 17);
        /* Setting PLLN to 200 */
        SET_BIT(RCC_PLLCFGR, 9);
        SET_BIT(RCC_PLLCFGR, 12);
        SET_BIT(RCC_PLLCFGR, 13);
        /* Setting PLLM to 2 */
        SET_BIT(RCC_PLLCFGR, 1);
    #else
        #warning "Invalid Configuration"
    #endif
}

/******************************************************************/
/* Func. Name: RCC_voidEnablePerClk                               */
/* i/p arguments: Copy_u8BusId: AHB1, AHB2, APB1, APB2            */
/* i/p arguments: Copy_u8PerId: 0 --> 31                          */
/* o/p arguments: nothing                                         */
/* Desc. : This API allows user to Enable clk for a specific per. */
/******************************************************************/
void RCC_voidEnablePerClk(u8 Copy_u8BusId, u8 Copy_u8PerId)
{  
    /* i/p validation */
    if ( (Copy_u8BusId > APB2) || (Copy_u8PerId > 31) )
    { /* Do Nothing */ }
    else
    {
        switch (Copy_u8BusId)
        {
        case AHB1: SET_BIT(RCC_AHB1ENR, Copy_u8PerId);
                   break;

        case AHB2: if (Copy_u8PerId != 7)
                   { /* Do Nothing */ }
                   else
                   { SET_BIT(RCC_AHB2ENR, Copy_u8PerId); }
                   break;

        case APB1: SET_BIT(RCC_APB1ENR, Copy_u8PerId);
                   break;

        case APB2: SET_BIT(RCC_APB2ENR, Copy_u8PerId);
                   break;

        default:
            break;
        }
    }
}

/*******************************************************************/
/* Func. Name: RCC_voidEnablePerClk                                */
/* i/p arguments: Copy_u8BusId: AHB1, AHB2, APB1, APB2             */
/* i/p arguments: Copy_u8PerId: 0 --> 31                           */
/* o/p arguments: nothing                                          */
/* Desc. : This API allows user to Disable clk for a specific per. */
/*******************************************************************/
void RCC_voidDisablePerClk(u8 Copy_u8BusId, u8 Copy_u8PerId)
{
    /* i/p validation */
    if ( (Copy_u8BusId > APB2) || (Copy_u8PerId > 31) )
    { /* Do Nothing */ }
    else
    {
        switch (Copy_u8BusId)
        {
        case AHB1: CLR_BIT(RCC_AHB1ENR, Copy_u8PerId);
                   break;

        case AHB2: if (Copy_u8PerId != 7)
                   { /* Do Nothing */ }
                   else
                   { CLR_BIT(RCC_AHB2ENR, Copy_u8PerId); }
                   break;

        case APB1: CLR_BIT(RCC_APB1ENR, Copy_u8PerId);
                   break;

        case APB2: CLR_BIT(RCC_APB2ENR, Copy_u8PerId);
                   break;

        default:
            break;
        }
    }
}
