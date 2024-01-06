#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "RCC_Interface.h"
#include "GPIO_Interface.h"
#include "STK_Interface.h"
#include "LEDMatrix8x8_Interface.h"
#include "STP_Interface.h"
#include "NVIC_Interface.h"
#include "EXTI_Interface.h"

/************************************ GPT SETTING FOR NOW ************************************/
/* Define the Registers */
#define TIM2_CR1        *((volatile u32*)0x40000000)
#define TIM2_CNT        *((volatile u32*)0x40000024)
#define TIM2_PSC        *((volatile u32*)0x40000028)
#define TIM2_ARR        *((volatile u32*)0x4000002C)
#define TIM2_SR         *((volatile u32*)0x40000010)
#define TIM2_DIER       *((volatile u32*)0x4000000C)
u8 APP_u8ToggleValue = 0;	// This variable is declared because Timer has an error, this is a quick method to solve the error
/*********************************************************************************************/

/******************************** GLOBAL VARIABLE ENIVORNMENT ********************************/
/* STICKS VARIABLES */
u8 APP_u8Stick1Pointer = 3;
/* SET THE BALL VARIABLES */
u8 APP_u8VerticalBall = 3;
u8 APP_u8VerticalDirection = 0;		// 1 means up, 0 means down
u8 APP_u8HorizontalBall = 4;
u8 APP_u8HorizontalDirection = 0;   // 0 means left, 1 means right
/* WHOLE SYSTEM FLAG VARIABLE */
u8 APP_u8SysFlag = 1;
/* SET THE MAIN FRAME */
u8 APP_u8Frame[8] = {24,0,0,0,8,0,0,0};
/*********************************************************************************************/

void APP_voidStick1UP()
{
	if (APP_u8Stick1Pointer == 0)
	{ /* Do Nothing */ }
	else
	{
		APP_u8Stick1Pointer--;
		APP_u8Frame[0] = (1 << APP_u8Stick1Pointer) + (1 << (APP_u8Stick1Pointer+1));
	}
}

void APP_voidStick1DOWN()
{
	if (APP_u8Stick1Pointer == 6)
	{ /* Do Nothing */ }
	else
	{
		APP_u8Stick1Pointer++;
		APP_u8Frame[0] = (1 << APP_u8Stick1Pointer) + (1 << (APP_u8Stick1Pointer+1));
	}
}


int main()
{
	/************************************ SYSTEM INITIALIZING ************************************/
	/* INIT System Clock */
	RCC_voidInitSysClk();
	/* Enable CLK for GPIOA and GPIOB */
	RCC_voidEnablePerClk(AHB1, GPIOAEN);
	RCC_voidEnablePerClk(AHB1, GPIOBEN);
	/* Enable SysTick */
	STK_voidInit();
	/* INIT STP */
	STP_voidInit();
	/* Enable EXTI */
	EXTI_voidInit();
	/* Set the Priority to be 4 Groups, 4 SubGroups */
	NVIC_voidSetPriorityConfig(G4_SG4);
	/*********************************************************************************************/



	/******************************** FOR EXTI0 --> UP the STICK1 ********************************/
	/* PB0 is INPUT, Pull Down */
	GPIO_voidSetPinMode(IOB, PIN0, INPUT);
	GPIO_voidSetPinPuPdConfig(IOB, PIN0, INPUT_PD);
	/* Enable LINE0 in EXTI */
	EXTI_voidSetEXTILineEnable(LINE0);
	/* LINE0 is connected to PB0, Sense the RISING_EDGE */
	EXTI_voidSetSenseControl(RISING_EDGE,LINE0);
	EXTI_voidSetEXTIPinConfig(IOB,LINE0);
	EXTI_voidSetCallBack(APP_voidStick1UP,LINE0);
	/* Set the priority of EXTI0 to be in G2SG2 */
	NVIC_voidSetPeriIntPriority(6,1,1);
	/*********************************************************************************************/


	/******************************* FOR EXTI1 --> DOWN the STICK *******************************/
	/* PB1 is INPUT, Pull Down */
	GPIO_voidSetPinMode(IOB, PIN1, INPUT);
	GPIO_voidSetPinPuPdConfig(IOB, PIN1, INPUT_PD);
	/* Enable LINE1 in EXTI */
	EXTI_voidSetEXTILineEnable(LINE1);
	/* LINE1 is connected to PB1, Sense the RISING_EDGE */
	EXTI_voidSetSenseControl(RISING_EDGE,LINE1);
	EXTI_voidSetEXTIPinConfig(IOB,LINE1);
	EXTI_voidSetCallBack(APP_voidStick1DOWN,LINE1);
	/* Set the priority of EXTI1 to be in G1SG2 */
	NVIC_voidSetPeriIntPriority(7,1,1);
	/********************************************************************************************/

	LEDMatrix8x8_voidDisplay(APP_u8Frame);

	/************************************* TIM2 INITIALIZING *************************************/
	RCC_voidEnablePerClk(APB1,TIM2EN);
	CLR_BIT(TIM2_CR1,4);
	TIM2_PSC = 0xF423;
	TIM2_ARR = 0xF;
	//SET_BIT(TIM2_DIER,6);
	SET_BIT(TIM2_DIER,0);
	NVIC_voidEnablePeriInt(28);
	NVIC_voidSetPeriIntPriority(28,1,2);
	SET_BIT(TIM2_CR1,0);
	/*********************************************************************************************/


	while (1)
	{
		if (APP_u8SysFlag == 1)
		{ LEDMatrix8x8_voidDisplay(APP_u8Frame); }
		else
		{
			/********************************* REINITIALIZE ALL VARIABLES ********************************/
			/* STICKS VARIABLES */
			APP_u8Stick1Pointer = 3;
			/* SET THE BALL VARIABLES */
			APP_u8VerticalBall = 3;
			APP_u8VerticalDirection = 0;
			APP_u8HorizontalBall = 4;
			APP_u8HorizontalDirection = 0;
			/* WHOLE SYSTEM FLAG VARIABLE */
			APP_u8SysFlag = 1;
			APP_u8Frame[0] = 24;
			APP_u8Frame[4] = 8;
			/*********************************************************************************************/
			int i = 0;
			for (i = 0;i < 1000000; i++)
			{ __asm volatile ("NOP");}
		}
	}
}


void TIM2_IRQHandler(void)
{
	if (APP_u8ToggleValue)
	{
		APP_u8ToggleValue = 1;
	}
	else
	{
		APP_u8Frame[APP_u8HorizontalBall] = 0 << APP_u8VerticalBall;
		/*************************************** CHECK GAME END CONDITION ***************************************/
		if (APP_u8HorizontalBall == 7)
		{ APP_u8HorizontalDirection = 0; }
		else if (APP_u8HorizontalBall == 1)
		{
			if ( (APP_u8VerticalBall == APP_u8Stick1Pointer) || (APP_u8VerticalBall == APP_u8Stick1Pointer+1) )
			{ APP_u8HorizontalDirection = 1; }
			else
			{ APP_u8SysFlag = 0; }
		}
		/********************************************************************************************************/


		/************************************ CHECK BOUNDARY GAME CONDITIONS ************************************/
		if (APP_u8VerticalBall == 7)
		{ APP_u8VerticalDirection = 1; }
		else if (APP_u8VerticalBall == 0)
		{ APP_u8VerticalDirection = 0; }
		/********************************************************************************************************/

		/***************************************** CHECK INC | DEC BALL *****************************************/
		if (APP_u8HorizontalDirection == 0)
		{ APP_u8HorizontalBall--; }
		else
		{ APP_u8HorizontalBall++; }

		if (APP_u8VerticalDirection == 0)
		{ APP_u8VerticalBall++; }
		else
		{ APP_u8VerticalBall--; }
		/********************************************************************************************************/
		APP_u8Frame[APP_u8HorizontalBall] = 1 << APP_u8VerticalBall;
		CLR_BIT(TIM2_SR,0);
		APP_u8ToggleValue = 0;
	}
}
