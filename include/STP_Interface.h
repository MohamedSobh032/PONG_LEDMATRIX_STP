/********************************************/
/* SWC: STP Driver                          */
/* Author: Mohamed Sobh                     */
/* Version: v0.0                            */
/* Date: 22 SEP 2023                        */
/* Description: This is the implem. of STP  */
/********************************************/
/* File Guard */
#ifndef STP_INTERFACE_H
#define STP_INTERFACE_H

void STP_voidInit();
void STP_voidSendSynch(u8 Copy_u8Data);
void STP_voidWriteFrameLEDMTX(u8 Copy_u8Data, u8 Copy_u8Column);

#endif