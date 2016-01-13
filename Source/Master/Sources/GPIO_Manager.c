/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: GPIO_Manager.c $
 * $Revision: 1.0 $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 11-01-2016 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file
 *		
*/
/*============================================================================*/
/* COPYRIGHT (C) CONTINENTAL AUTOMOTIVE 2014                                  */
/* AUTOMOTIVE GROUP, Interior Division, Body and Security                     */
/* ALL RIGHTS RESERVED                                                        */
/*                                                                            */
/* The reproduction, transmission, or use of this document or its content is  */
/* not permitted without express written authority. Offenders will be liable  */
/* for damages.                                                               */
/* All rights, including rights created by patent grant or registration of a  */
/* utility model or design, are reserved.                                     */
/*                                                                            */
/*============================================================================*/
/*============================================================================*/
/*                    REUSE HISTORY - taken over from                         */
/*============================================================================*/
/*  DATABASE           |        PROJECT     | FILE VERSION (AND INSTANCE)     */
/*----------------------------------------------------------------------------*/
/*                     |     Cluster_EA      |         1.0                    */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: GPIO_Manager.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "GPIO_Manager.h"

/* Defines */
/*============================================================================*/
#define TRANSISTOR_1 SIU.GPDO[7].B.PDO
#define TRANSISTOR_2 SIU.GPDO[8].B.PDO
#define TRANSISTOR_3 SIU.GPDO[9].B.PDO

T_UBYTE ruw_Display_Selector = 0;

T_UBYTE ruw_Display_Number1 = 0;
T_UBYTE ruw_Display_Number2 = 0;
T_UBYTE ruw_Display_Number3 = 0;

/*==============================================================================
* Function: Init_GPIO
* 
* Description: 
*
==============================================================================*/
void Init_GPIO (void){
	
	T_UBYTE lub_i = 0;
	
	for(lub_i = 0; lub_i <= 3; lub_i++){	
		Set_Pin_Mode(BOARD_LEDS + lub_i, OUT);
		Set_Pin_State( BOARD_LEDS + lub_i, LED_OFF);
	}
	
	/*	Input configuration*/
	for(lub_i = 0; lub_i <= 9; lub_i++){	/*	7 segment displays initialization */	
		Set_Pin_Mode(PORTA + lub_i, OUT);
		Set_Pin_State( PORTA + lub_i, OFF);
	}
	
	for(lub_i = 0; lub_i <= 4; lub_i++){	/*	led indicator initialization	*/
		Set_Pin_Mode(PORTG + lub_i, OUT);
		Set_Pin_State( PORTG + lub_i, OFF);
	}
	
	for(lub_i = 0; lub_i <= 6; lub_i++){	/*	led bar initialization */
		Set_Pin_Mode(PORTD + lub_i, OUT);
		Set_Pin_State( PORTD + lub_i, OFF);
	}
	
	for(lub_i = 0; lub_i <= 6; lub_i++){	/*	LCD initialization */
		Set_Pin_Mode(PORTF + lub_i, OUT);
		Set_Pin_State( PORTF + lub_i, OFF);
	}
	
	//Output configuration
	Set_Pin_Mode(PORTG + 5, IN);	/*	switch bat		*/
	Set_Pin_Mode(PORTG + 6, IN);	/*	switch ignition	*/
	Set_Pin_Mode(PORTG + 7, IN);	/*	reset trip-odo	*/
	Set_Pin_Mode(PORTD + 7, IN);	/*	unit selector	*/
	
	Set_Pin_Mode(64, IN);	/*	switch bat		*/
	Set_Pin_Mode(65, IN);	/*	switch ignition	*/
	Set_Pin_Mode(66, IN);	/*	reset trip-odo	*/
	Set_Pin_Mode(67, IN);	/*	unit selector	*/
	
}
/*==============================================================================
* Function: Set_LCD_Data_Output
* 
* Description: 
*
==============================================================================*/
void Set_LCD_Data_Output(void){

	T_UBYTE lub_i = 0;
	for(lub_i = 0; lub_i <= 3; lub_i++){
		Set_Pin_Mode(PORTF + lub_i, OUT);
	}
	
}
/*==============================================================================
* Function: Set_LCD_Data_Input
* 
* Description: 
*
==============================================================================*/
void Set_LCD_Data_Input(void){
	
	T_UBYTE lub_i = 0;
	for(lub_i = 0; lub_i <= 3; lub_i++){
		Set_Pin_Mode(PORTF + lub_i, IN);
	}
	
}
/*==============================================================================
* Function: Set_LCD_E
* 
* Description: 
*
==============================================================================*/
void Set_LCD_E(T_UBYTE State){
	
	Set_Pin_State(LCD_E, State);

}
/*==============================================================================
* Function: Set_LCD_RW
* 
* Description: 
*
==============================================================================*/
void Set_LCD_RW(T_UBYTE State){
	
	Set_Pin_State(LCD_RW, State);

}
/*==============================================================================
* Function: Set_LCD_RS
* 
* Description: 
*
==============================================================================*/
void Set_LCD_RS(T_UBYTE State){
	
	Set_Pin_State(LCD_RS, State);

}
/*==============================================================================
* Function: Read_LCD_Data
* 
* Description: 
*
==============================================================================*/
T_UBYTE Read_LCD_Data(void){
	
	//Get_Pin_State_IN(PIN_LCD_DATA_0);
	return (Get_Pin_State_IN(PIN_LCD_DATA_0) +  (Get_Pin_State_IN(PIN_LCD_DATA_1)<<1) + (Get_Pin_State_IN(PIN_LCD_DATA_2)<<2) +  (Get_Pin_State_IN(PIN_LCD_DATA_3)<<3));
	//return (LCD_DATA_STATE_0 +  (LCD_DATA_STATE_1<<1) + (LCD_DATA_STATE_2<<2) +  (LCD_DATA_STATE_3<<3));
	
}
/*==============================================================================
* Function: Set_LCD_Data
* 
* Description: 
*
==============================================================================*/
void Set_LCD_Data(T_UBYTE Data_Pin,T_UBYTE State){
	
	Set_Pin_State( PORTF + Data_Pin, State);
	
}
/*==============================================================================
* Function: Set_LCD_Data
* 
* Description: 
*
==============================================================================*/
void Display_Speed(void){
	
typedef enum re_LEDS{
	LED_E,
	LED_D,
	LED_C,
	LED_B,
	LED_A,
	LED_F,
	LED_G
};

T_UBYTE laub_LEDS[7] = { LED_A, LED_B, LED_C, LED_D, LED_E, LED_F, LED_G};

typedef T_UBYTE Num[7];
Num Numbers[10] = {{ 1, 1, 1, 1, 1, 1, 0},
				   { 0, 1, 1, 0, 0, 0, 0},
				   { 1, 1, 0, 1, 1, 0, 1},
				   { 1, 1, 1, 1, 0, 0, 1},
				   { 0, 1, 1, 0, 0, 1, 1},
				   { 1, 0, 1, 1, 0, 1, 1},
				   { 1, 0, 1, 1, 1, 1, 1},
				   { 1, 1, 1, 0, 0, 0, 0},
				   { 1, 1 ,1 ,1 ,1 ,1, 1},
				   { 1, 1, 1, 1, 0, 1, 1}};
	
T_UBYTE lub_i;
	
	switch (ruw_Display_Selector){
		case 0:
			TRANSISTOR_1 = OFF;
			TRANSISTOR_2 = OFF;
			TRANSISTOR_3 = ON;
			for(lub_i = 0; lub_i <= 6; lub_i++){
				Set_Pin_State( laub_LEDS[lub_i], Numbers[ruw_Display_Number1][lub_i]);
			}
			ruw_Display_Selector++;
		break;
		case 1:
			TRANSISTOR_1 = OFF;
			TRANSISTOR_2 = ON;
			TRANSISTOR_3 = OFF;
			for(lub_i = 0; lub_i <= 6; lub_i++){
				Set_Pin_State( laub_LEDS[lub_i], Numbers[ruw_Display_Number2][lub_i]);
			}
			ruw_Display_Selector++;
			break;
		case 2:
			TRANSISTOR_1 = ON;
			TRANSISTOR_2 = OFF;
			TRANSISTOR_3 = OFF;
			for(lub_i = 0; lub_i <= 6; lub_i++){
				Set_Pin_State( laub_LEDS[lub_i], Numbers[ruw_Display_Number3][lub_i]);
			}
			ruw_Display_Selector = 0;
			break;
		default:
			/* Do nothing */
		break;
		
	}

}
