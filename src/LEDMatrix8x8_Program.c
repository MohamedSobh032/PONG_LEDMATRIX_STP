/****************************************************/
/* SWC: LEDMatrix8x8 Driver                         */
/* Author: Mohamed Sobh                             */
/* Version: v0.0                                    */
/* Date: 26 AUG 2023                                */
/* Description: This is the implem. of LEDMatrix8x8 */
/****************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "LEDMatrix8x8_Interface.h"
#include "LEDMatrix8x8_Private.h"
#include "LEDMatrix8x8_Config.h"

#include "GPIO_Interface.h"
#include "STK_Interface.h"

#include "STP_Interface.h"

/**************************************************/
/* Func. Name: LEDMatrix8x8_voidInit              */
/* i/p arguments: nothing                         */
/* o/p arguments: nothing                         */
/* Desc. : This API initialize the LED MAT        */
/**************************************************/
void LEDMatrix8x8_voidInit()
{
    /* Set the Columns as Output */
    GPIO_voidSetPinMode(LEDMAT8x8_COL0, OUTPUT);
    GPIO_voidSetPinMode(LEDMAT8x8_COL1, OUTPUT);
    GPIO_voidSetPinMode(LEDMAT8x8_COL2, OUTPUT);
    GPIO_voidSetPinMode(LEDMAT8x8_COL3, OUTPUT);
    GPIO_voidSetPinMode(LEDMAT8x8_COL4, OUTPUT);
    GPIO_voidSetPinMode(LEDMAT8x8_COL5, OUTPUT);
    GPIO_voidSetPinMode(LEDMAT8x8_COL6, OUTPUT);
    GPIO_voidSetPinMode(LEDMAT8x8_COL7, OUTPUT);

    /* Set the Rows as Output */
    GPIO_voidSetPinMode(LEDMAT8x8_ROW0, OUTPUT);
    GPIO_voidSetPinMode(LEDMAT8x8_ROW1, OUTPUT);
    GPIO_voidSetPinMode(LEDMAT8x8_ROW2, OUTPUT);
    GPIO_voidSetPinMode(LEDMAT8x8_ROW3, OUTPUT);
    GPIO_voidSetPinMode(LEDMAT8x8_ROW4, OUTPUT);
    GPIO_voidSetPinMode(LEDMAT8x8_ROW5, OUTPUT);
    GPIO_voidSetPinMode(LEDMAT8x8_ROW6, OUTPUT);
    GPIO_voidSetPinMode(LEDMAT8x8_ROW7, OUTPUT);

    /*Set Columns Output as Push Pull */
	GPIO_voidSetPinType(LEDMAT8x8_COL0, OUTPUT_PP);
    GPIO_voidSetPinType(LEDMAT8x8_COL1, OUTPUT_PP);
    GPIO_voidSetPinType(LEDMAT8x8_COL2, OUTPUT_PP);
    GPIO_voidSetPinType(LEDMAT8x8_COL3, OUTPUT_PP);
    GPIO_voidSetPinType(LEDMAT8x8_COL4, OUTPUT_PP);
    GPIO_voidSetPinType(LEDMAT8x8_COL5, OUTPUT_PP);
    GPIO_voidSetPinType(LEDMAT8x8_COL6, OUTPUT_PP);
    GPIO_voidSetPinType(LEDMAT8x8_COL7, OUTPUT_PP);

    /*Set Rows Output as Push Pull */
	GPIO_voidSetPinType(LEDMAT8x8_ROW0, OUTPUT_PP);
    GPIO_voidSetPinType(LEDMAT8x8_ROW1, OUTPUT_PP);
    GPIO_voidSetPinType(LEDMAT8x8_ROW2, OUTPUT_PP);
    GPIO_voidSetPinType(LEDMAT8x8_ROW3, OUTPUT_PP);
    GPIO_voidSetPinType(LEDMAT8x8_ROW4, OUTPUT_PP);
    GPIO_voidSetPinType(LEDMAT8x8_ROW5, OUTPUT_PP);
    GPIO_voidSetPinType(LEDMAT8x8_ROW6, OUTPUT_PP);
    GPIO_voidSetPinType(LEDMAT8x8_ROW7, OUTPUT_PP);

    /* Set Columns Speed to be Medium */
    GPIO_voidSetPinSpeed(LEDMAT8x8_COL0, OUTPUT_MS);
    GPIO_voidSetPinSpeed(LEDMAT8x8_COL1, OUTPUT_MS);
    GPIO_voidSetPinSpeed(LEDMAT8x8_COL2, OUTPUT_MS);
    GPIO_voidSetPinSpeed(LEDMAT8x8_COL3, OUTPUT_MS);
    GPIO_voidSetPinSpeed(LEDMAT8x8_COL4, OUTPUT_MS);
    GPIO_voidSetPinSpeed(LEDMAT8x8_COL5, OUTPUT_MS);
    GPIO_voidSetPinSpeed(LEDMAT8x8_COL6, OUTPUT_MS);
    GPIO_voidSetPinSpeed(LEDMAT8x8_COL7, OUTPUT_MS);

    /* Set Rows Speed to be Medium */
    GPIO_voidSetPinSpeed(LEDMAT8x8_ROW0, OUTPUT_MS);
    GPIO_voidSetPinSpeed(LEDMAT8x8_ROW1, OUTPUT_MS);
    GPIO_voidSetPinSpeed(LEDMAT8x8_ROW2, OUTPUT_MS);
    GPIO_voidSetPinSpeed(LEDMAT8x8_ROW3, OUTPUT_MS);
    GPIO_voidSetPinSpeed(LEDMAT8x8_ROW4, OUTPUT_MS);
    GPIO_voidSetPinSpeed(LEDMAT8x8_ROW5, OUTPUT_MS);
    GPIO_voidSetPinSpeed(LEDMAT8x8_ROW6, OUTPUT_MS);
    GPIO_voidSetPinSpeed(LEDMAT8x8_ROW7, OUTPUT_MS);
}

/*********************************************/
/* Func. Name: LEDMatrix8x8_voidSetColumns   */
/* i/p arguments: nothing                    */
/* o/p arguments: nothing                    */
/* Desc. : This API set the columns to write */
/*********************************************/
static void LEDMatrix8x8_voidSetColumns()
{
    GPIO_voidSetPinValue(LEDMAT8x8_COL0, OUTPUT_HIGH);
    GPIO_voidSetPinValue(LEDMAT8x8_COL1, OUTPUT_HIGH);
    GPIO_voidSetPinValue(LEDMAT8x8_COL2, OUTPUT_HIGH);
    GPIO_voidSetPinValue(LEDMAT8x8_COL3, OUTPUT_HIGH);
    GPIO_voidSetPinValue(LEDMAT8x8_COL4, OUTPUT_HIGH);
    GPIO_voidSetPinValue(LEDMAT8x8_COL5, OUTPUT_HIGH);
    GPIO_voidSetPinValue(LEDMAT8x8_COL6, OUTPUT_HIGH);
    GPIO_voidSetPinValue(LEDMAT8x8_COL7, OUTPUT_HIGH);
}

/*********************************************/
/* Func. Name: LEDMatrix8x8_voidWriteRows    */
/* i/p arguments: nothing                    */
/* o/p arguments: nothing                    */
/* Desc. : This API Write on the Rows        */
/*********************************************/
static void LEDMatrix8x8_voidWriteRows(u8 Copy_u8Row)
{
    GPIO_voidSetPinValue(LEDMAT8x8_ROW0, GET_BIT(Copy_u8Row, LEDMAT8x8_ROW0));
    GPIO_voidSetPinValue(LEDMAT8x8_ROW1, GET_BIT(Copy_u8Row, LEDMAT8x8_ROW1));
    GPIO_voidSetPinValue(LEDMAT8x8_ROW2, GET_BIT(Copy_u8Row, LEDMAT8x8_ROW2));
    GPIO_voidSetPinValue(LEDMAT8x8_ROW3, GET_BIT(Copy_u8Row, LEDMAT8x8_ROW3));
    GPIO_voidSetPinValue(LEDMAT8x8_ROW4, GET_BIT(Copy_u8Row, LEDMAT8x8_ROW4));
    GPIO_voidSetPinValue(LEDMAT8x8_ROW5, GET_BIT(Copy_u8Row, LEDMAT8x8_ROW5));
    GPIO_voidSetPinValue(LEDMAT8x8_ROW6, GET_BIT(Copy_u8Row, LEDMAT8x8_ROW6));
    GPIO_voidSetPinValue(LEDMAT8x8_ROW7, GET_BIT(Copy_u8Row, LEDMAT8x8_ROW7));
}

/*********************************************/
/* Func. Name: LEDMatrix8x8_voidDisplay      */
/* i/p arguments: Copy_u8Frame               */
/* o/p arguments: nothing                    */
/* Desc. : This API Write the whole frame    */
/*********************************************/
void LEDMatrix8x8_voidDisplay(u8 *Copy_u8Frame)
{
    #if PIN_CONFIG == STP_PINS
        u8 Local_u8Counter = 0;
        u8 Local_u8Column = 0;
        for (Local_u8Counter = 0; Local_u8Counter < 8; Local_u8Counter++)
        {
            /* Initializing Columns */
            Local_u8Column = 255;
            /* Set the Column you want to write in to 0 */
            CLR_BIT(Local_u8Column, Local_u8Counter);
            STP_voidWriteFrameLEDMTX(Copy_u8Frame[Local_u8Counter], Local_u8Column);
            STK_voidSetBusyWait(2500) ; //2.5ms
        }
    #elif PIN_CONFIG == NORMAL_PINS
        u8 Local_u8Counter = 0;
        for (Local_u8Counter = 0; Local_u8Counter < 8; Local_u8Counter++)
        {
	        LEDMatrix8x8_voidSetColumns();
	        LEDMatrix8x8_voidWriteRows(Copy_u8Frame[Local_u8Counter]);
	        GPIO_voidSetPinValue(LEDMAT8x8_COL_PORT, Local_u8Counter, OUTPUT_LOW);
	        STK_voidSetBusyWait(2500) ; //2.5ms
        }
    #else
        #warning "Invalid Configurations"
    #endif
}
