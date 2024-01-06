/********************************************/
/* SWC: STP Driver                          */
/* Author: Mohamed Sobh                     */
/* Version: v0.0                            */
/* Date: 22 SEP 2023                        */
/* Description: This is the implem. of STP  */
/********************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "STP_Interface.h"
#include "STP_Config.h"
#include "STP_Private.h"

#include "GPIO_Interface.h"
#include "STK_Interface.h"
/************************************/
/* Func. Name: STP_voidInit         */
/* i/p arguments: Nothing           */
/* o/p arguments: Nothing           */
/* Desc. : This API initializes STP */
/************************************/
void STP_voidInit()
{
    GPIO_voidSetPinMode(SERIAL_PIN, OUTPUT);
    GPIO_voidSetPinType(SERIAL_PIN, OUTPUT_PP);
    GPIO_voidSetPinSpeed(SERIAL_PIN, OUTPUT_MS);

    GPIO_voidSetPinMode(SHIFT_CLK_PIN, OUTPUT);
    GPIO_voidSetPinType(SHIFT_CLK_PIN, OUTPUT_PP);
    GPIO_voidSetPinSpeed(SHIFT_CLK_PIN, OUTPUT_MS);

    GPIO_voidSetPinMode(STORE_CLK_PIN, OUTPUT);
    GPIO_voidSetPinType(STORE_CLK_PIN, OUTPUT_PP);
    GPIO_voidSetPinSpeed(STORE_CLK_PIN, OUTPUT_MS);
}

/***************************************/
/* Func. Name: STP_voidSendSynch       */
/* i/p arguments: Copy_u8Data          */
/* o/p arguments: Nothing              */
/* Desc. : This API writes on STP Pins */
/***************************************/
void STP_voidSendSynch(u8 Copy_u8Data)
{
    s8 Local_s8Counter = 7;
    for (Local_s8Counter = 7; Local_s8Counter >= 0; Local_s8Counter--)
    {
        /* Write on the SERIAL_PIN */
        GPIO_voidSetPinValue(SERIAL_PIN, GET_BIT(Copy_u8Data, Local_s8Counter));
        /* CLK ON SHIFT_CLK_PIN */
        GPIO_voidSetPinValue(SHIFT_CLK_PIN, OUTPUT_HIGH);
        STK_voidSetBusyWait(1);
        GPIO_voidSetPinValue(SHIFT_CLK_PIN, OUTPUT_LOW);
        STK_voidSetBusyWait(1);
    }
    GPIO_voidSetPinValue(STORE_CLK_PIN, OUTPUT_HIGH);
    STK_voidSetBusyWait(1);
    GPIO_voidSetPinValue(STORE_CLK_PIN, OUTPUT_LOW);
    STK_voidSetBusyWait(1);
}

/****************************************/
/* Func. Name: STP_voidWriteFrameLEDMTX */
/* i/p arguments: Copy_u16Data          */
/* o/p arguments: Nothing               */
/* Desc. : This API writes on LEDMTX    */
/****************************************/
void STP_voidWriteFrameLEDMTX(u8 Copy_u8Data, u8 Copy_u8Column)
{
    s8 Local_s8Counter = 7;

    for (Local_s8Counter = 7; Local_s8Counter >= 0; Local_s8Counter--)
    {
        /* Write the Column */
        GPIO_voidSetPinValue(SERIAL_PIN, GET_BIT(Copy_u8Column, Local_s8Counter));
        /* CLK ON SHIFT_CLK_PIN */
        GPIO_voidSetPinValue(SHIFT_CLK_PIN, OUTPUT_HIGH);
        STK_voidSetBusyWait(1);
        GPIO_voidSetPinValue(SHIFT_CLK_PIN, OUTPUT_LOW);
        STK_voidSetBusyWait(1);
    }

    for (Local_s8Counter = 7; Local_s8Counter >= 0; Local_s8Counter--)
    {
        /* Write on the SERIAL_PIN */
        GPIO_voidSetPinValue(SERIAL_PIN, GET_BIT(Copy_u8Data, Local_s8Counter));
        /* CLK ON SHIFT_CLK_PIN */
        GPIO_voidSetPinValue(SHIFT_CLK_PIN, OUTPUT_HIGH);
        STK_voidSetBusyWait(1);
        GPIO_voidSetPinValue(SHIFT_CLK_PIN, OUTPUT_LOW);
        STK_voidSetBusyWait(1);
    }

    GPIO_voidSetPinValue(STORE_CLK_PIN, OUTPUT_HIGH);
    STK_voidSetBusyWait(1);
    GPIO_voidSetPinValue(STORE_CLK_PIN, OUTPUT_LOW);
    STK_voidSetBusyWait(1);
}


