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

/*==============================================================================
* Function: Init_GPIO
* 
* Description: 
*
==============================================================================*/
void Init_GPIO (void){
	
	T_UBYTE lub_i = 0;
	
	for(lub_i = 0; lub_i <= 3; lub_i++){	/*	7 segment displays initialization */	
		Set_Pin_Mode(BOARD_LEDS + lub_i, OUT);
		Set_Pin_State( BOARD_LEDS + lub_i, OFF);
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
		Set_Pin_State( PORTF + lub_i, OFF);
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
