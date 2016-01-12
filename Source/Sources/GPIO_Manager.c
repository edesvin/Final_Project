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
#define LED_OFF 1
#define LED_ON	0

#define TRANSISTOR_1 7
#define TRANSISTOR_2 8
#define TRANSISTOR_3 9

T_UBYTE ruw_Display_Selector = 0;

static T_UBYTE ruw_Display_Number1;
static T_UBYTE ruw_Display_Number2;
static T_UBYTE ruw_Display_Number3;

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
	
	return (Get_Pin_State_IN(PIN_LCD_DATA_0) +  (Get_Pin_State_IN(PIN_LCD_DATA_1)<<1) + (Get_Pin_State_IN(PIN_LCD_DATA_2)<<2) +  (Get_Pin_State_IN(PIN_LCD_DATA_3)<<3));
	
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
void Display_Speed(T_UWORD luw_speed){

	Data_Module(luw_speed);

	switch (ruw_Display_Selector){
		case 0:
			Set_Transistors(ruw_Display_Selector);
			Print_Display_Number(ruw_Display_Number1);
			ruw_Display_Selector = 1;
			break;
		case 1:
			Set_Transistors(ruw_Display_Selector);
			Print_Display_Number(ruw_Display_Number2);
			ruw_Display_Selector = 2;
			break;
		case 2:
			Set_Transistors(ruw_Display_Selector);			
			Print_Display_Number(ruw_Display_Number3);
			ruw_Display_Selector = 0;
			break;
		default:
			/* Do nothing */
			break;
		
	}

}
/*==============================================================================
* Function: Data_Module
* 
* Description: 
*
==============================================================================*/
void Data_Module(T_UWORD luw_Data){
	
	ruw_Display_Number1 = luw_Data / 100;
	luw_Data = luw_Data % 100;
	ruw_Display_Number2 = luw_Data / 10;
	ruw_Display_Number3 = luw_Data % 10;
	
}
/*==============================================================================
* Function: Set_Transistors
* 
* Description: 
*
==============================================================================*/
void Set_Transistors(T_UBYTE lub_transistor){
	
	T_UBYTE lub_i;
	
	for(lub_i = 0; lub_i<=2; lub_i++){
		Set_Pin_State(TRANSISTOR_1 + lub_i, OFF);
	}
	
	switch(lub_transistor){
		case 0:
			Set_Pin_State(TRANSISTOR_1, ON);
			break;
		case 1:
			Set_Pin_State(TRANSISTOR_2, ON);
			break;
		case 2:
			Set_Pin_State(TRANSISTOR_3, ON);
			break;
		default:
			break;
	}
	
}
/*==============================================================================
* Function: Print_Display_Number
* 
* Description: 
*
==============================================================================*/
void Print_Display_Number(T_UBYTE lub_Number){
	
	T_UBYTE lub_i;
	typedef enum re_LEDS{
		LED_E,
		LED_D,
		LED_C,
		LED_B,
		LED_A,
		LED_F,
		LED_G
	};
	T_UBYTE laub_LEDS[7] = { LED_A, LED_B, LED_C, LED_D, LED_E, LED_F, LED_G };
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
	
	
	for(lub_i = 0; lub_i <= 6; lub_i++){
		Set_Pin_State( laub_LEDS[lub_i], Numbers[lub_Number][lub_i]);
	}
}
