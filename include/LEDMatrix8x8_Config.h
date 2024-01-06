/****************************************************/
/* SWC: LEDMatrix8x8 Driver                         */
/* Author: Mohamed Sobh                             */
/* Version: v0.0                                    */
/* Date: 26 AUG 2023                                */
/* Description: This is the implem. of LEDMatrix8x8 */
/****************************************************/
/* File Guard */
#ifndef LEDMATRI8X8_CONFIG_H
#define LEDMATRI8X8_CONFIG_H

/* Which Port will be used to write on the Rows */
#define LEDMAT8x8_ROW0          IOB,PIN0
#define LEDMAT8x8_ROW1          IOB,PIN1
#define LEDMAT8x8_ROW2          IOB,PIN2
#define LEDMAT8x8_ROW3          IOB,PIN3
#define LEDMAT8x8_ROW4          IOB,PIN4
#define LEDMAT8x8_ROW5          IOB,PIN5
#define LEDMAT8x8_ROW6          IOB,PIN6
#define LEDMAT8x8_ROW7          IOB,PIN7

/* Which Port will be used to write on the Columns */
#define LEDMAT8x8_COL_PORT      IOA
#define LEDMAT8x8_COL0          IOA,PIN0
#define LEDMAT8x8_COL1          IOA,PIN1
#define LEDMAT8x8_COL2          IOA,PIN2
#define LEDMAT8x8_COL3          IOA,PIN3
#define LEDMAT8x8_COL4          IOA,PIN4
#define LEDMAT8x8_COL5          IOA,PIN5
#define LEDMAT8x8_COL6          IOA,PIN6
#define LEDMAT8x8_COL7          IOA,PIN7


/* Which type of connections will be used */
#define PIN_CONFIG          STP


#endif