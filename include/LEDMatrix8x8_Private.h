/****************************************************/
/* SWC: LEDMatrix8x8 Driver                         */
/* Author: Mohamed Sobh                             */
/* Version: v0.0                                    */
/* Date: 26 AUG 2023                                */
/* Description: This is the implem. of LEDMatrix8x8 */
/****************************************************/
/* File Guard */
#ifndef LEDMATRI8X8_PRIVATE_H
#define LEDMATRI8X8_PRIVATE_H

static void LEDMatrix8x8_voidSetColumns();
static void LEDMatrix8x8_voidWriteRows(u8 Copy_u8Row);

/* STP or Normal Pins */
#define STP_PINS        0
#define NORMAL_PINS     1

#endif