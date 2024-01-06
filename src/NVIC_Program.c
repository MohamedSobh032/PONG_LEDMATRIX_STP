/**********************************************/
/* SWC: NVIC Driver                           */
/* Author: Mohamed Sobh                       */
/* Version: v0.0                              */
/* Date: 19 AUG 2023                          */
/* Description: This is the implem. of NVIC   */
/**********************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "NVIC_Interface.h"
#include "NVIC_Private.h"
#include "NVIC_Config.h"

static u8 Global_u8PriorityConfig;

/******************************************************************/
/* Func. Name: NVIC_voidEnablePeriInt                             */
/* i/p arguments: Copy_u8PeriId                                   */
/* o/p arguments: Nothing                                         */
/* Desc. : This API allows to enable interrupt for specific Peri. */
/******************************************************************/
void NVIC_voidEnablePeriInt(u8 Copy_u8PeriId)
{ NVIC->ISER[(Copy_u8PeriId/32)] = 1 << (Copy_u8PeriId%32); }


/*******************************************************************/
/* Func. Name: NVIC_voidDisablePeriInt                             */
/* i/p arguments: Copy_u8PeriId                                    */
/* o/p arguments: Nothing                                          */
/* Desc. : This API allows to disable interrupt for specific Peri. */
/*******************************************************************/
void NVIC_voidDisablePeriInt(u8 Copy_u8PeriId)
{ NVIC->ICER[(Copy_u8PeriId/32)] = 1 << (Copy_u8PeriId%32); }


/*************************************************************/
/* Func. Name: NVIC_voidSetPendingFlag                       */
/* i/p arguments: Copy_u8PeriId                              */
/* o/p arguments: Nothing                                    */
/* Desc. : This API Set the Pending Flag of a specific Peri. */
/*************************************************************/
void NVIC_voidSetPendingFlag(u8 Copy_u8PeriId)
{ NVIC->ISPR[(Copy_u8PeriId/32)] = 1 << (Copy_u8PeriId%32); }

/***************************************************************/
/* Func. Name: NVIC_voidClearPendingFlag                       */
/* i/p arguments: Copy_u8PeriId                                */
/* o/p arguments: Nothing                                      */
/* Desc. : This API Clear the Pending Flag of a specific Peri. */
/***************************************************************/
void NVIC_voidClearPendingFlag(u8 Copy_u8PeriId)
{ NVIC->ICPR[(Copy_u8PeriId/32)] = 1 << (Copy_u8PeriId%32); }

/**********************************************************************************/
/* Func. Name: NVIC_voidSetPriorityConfig                                         */
/* i/p arguments: Copy_u8PriorityConfig: G16_SG0, G8_SG2, G4_SG4, G2_SG8, G0_SG16 */
/* o/p arguments: Nothing                                                         */
/* Desc. : This API allows to Set number of groups and subgroups                  */
/**********************************************************************************/
void NVIC_voidSetPriorityConfig(u8 Copy_u8PriorityConfig)
{
    if (Copy_u8PriorityConfig > G0_SG16)
    { /* Do Nothing */ }
    else
    {
        switch (Copy_u8PriorityConfig)
        {
            case G16_SG0:   SCB_AIRCR = VECT_KEY | (G4BITS_SG0BITS << 8);
                            Global_u8PriorityConfig = G4BITS_SG0BITS;
                            break;
            case G8_SG2:    SCB_AIRCR = VECT_KEY | (G3BITS_SG1BITS << 8);
                            Global_u8PriorityConfig = G3BITS_SG1BITS;
                            break;
            case G4_SG4:    SCB_AIRCR = VECT_KEY | (G2BITS_SG2BITS << 8);
                            Global_u8PriorityConfig = G2BITS_SG2BITS;
                            break;
            case G2_SG8:    SCB_AIRCR = VECT_KEY | (G1BITS_SG3BITS << 8);
                            Global_u8PriorityConfig = G1BITS_SG3BITS;
                            break;
            case G0_SG16:   SCB_AIRCR = VECT_KEY | (G0BITS_SG4BITS << 8);
                            Global_u8PriorityConfig = G0BITS_SG4BITS;
                            break;
        }
    }
}

/******************************************************************/
/* Func. Name: NVIC_voidSetPeriIntPriority                        */
/* i/p arguments: Copy_u8PeriId                                   */
/* i/p arguments: Copy_u8GroupId                                  */
/* i/p arguments: Copy_u8SubGroupId                               */
/* o/p arguments: Nothing                                         */
/* Desc. : This API allows to Set a Peri. to a Group and Subgroup */
/******************************************************************/
void NVIC_voidSetPeriIntPriority(u8 Copy_u8PeriId, u8 Copy_u8GroupId, u8 Copy_u8SubGroupId)
{
    u8 Local_u8Priority = Copy_u8SubGroupId | (Copy_u8GroupId << (Global_u8PriorityConfig - 3));
    NVIC->IPR[Copy_u8PeriId] = Local_u8Priority << 4;
}
