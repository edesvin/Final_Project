/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: TASKS.c $
 * $Revision: 1.0 $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 07-01-2016 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file
    It holds the implementation of the functions that contain the tasks.
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
/*                     |       Cluster_EA   |         1.0                      */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: TASKS.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "TASKS.h"
#include "ADC.h"
#include "LCD.h"
#include "Can_Manager.h"

#define BUTTON_1 64
#define BUTTON_2 65
#define BUTTON_3 66
#define BUTTON_4 67

extern T_UBYTE ruw_Display_Number1;
extern T_UBYTE ruw_Display_Number2;
extern T_UBYTE ruw_Display_Number3;

T_UBYTE button1 = 0;
T_UBYTE button2 = 0;
T_UBYTE button3 = 0;
T_UBYTE button4 = 0;
/*==============================================================================
* Function: Task0_3ms
* Description: 
*
==============================================================================*/
void Task0_3ms(void){
	if( Get_Pin_State_IN(BUTTON_1) ){
		button1++;
		if(button1 == 5){
			 rs_indicators.Opened_Doors ^= 1;
		}else if(button1 == 6){
			button1 = 5;
		}else{
			/* Do nothing */
		}
	}else{
		button1 = 0;
	}
	
	if( Get_Pin_State_IN(BUTTON_2) ){
		button2++;
		if(button2 == 5){
			 rs_indicators.Seat_Belt ^= 1;
		}else if(button2 == 6){
			button2 = 5;
		}else{
			/* Do nothing */
		}
	}else{
		button2 = 0;
	}
	
	if( Get_Pin_State_IN(BUTTON_3) ){
		button3++;
		if(button3 == 5){
			 rs_indicators.High_Beams ^= 1;
		}else if(button3 == 6){
			button3 = 5;
		}else{
			/* Do nothing */
		}
	}else{
		button3 = 0;
	}
	
	if( Get_Pin_State_IN(BUTTON_4) ){
		button4++;
		if(button4 == 5){
			 rs_indicators.Emergency_Break ^= 1;
		}else if(button4 == 6){
			button4 = 5;
		}else{
			/* Do nothing */
		}
	}else{
		button4 = 0;
	}
}
/*==============================================================================
* Function: Task1_10ms
* Description: 
*
==============================================================================*/
void Task1_5ms(void){
	/* Display_Speed(); */
	Display_Speed();
	
#ifdef TRANSMITTER
	CanManager_SendMessage_12p5ms();
#endif
}

/*==============================================================================
* Function: Task2_50ms
* Description: 
*
==============================================================================*/
void Task2_50ms(void){

	/* Update_speedometer(); */
#ifdef TRANSMITTER
	CanManager_SendMessage_25ms();
#endif
}

/*==============================================================================
* Function: Task3_100ms
* Description: 
*
==============================================================================*/
void Task3_100ms(void){
	/* Update_fuel();  */
#ifdef TRANSMITTER
	CanManager_SendMessage_100ms();
	#endif
}

/*==============================================================================
* Function: Task4_200ms
* Description: 
*
==============================================================================*/
void Task4_200ms(void){
	/* Update_odometer();   */
}

/*==============================================================================
* Function: Task5_250ms
* Description: 
*
==============================================================================*/
void Task5_250ms(void){
	/* Get_switches_State();
	 * Update_indicators(); */
	CanManager_Send_Speed();
	CanManager_Send_Fuel_Level();
	CanManager_Send_Indicators();
	CanManager_Send_Odometer_Increment();
}
/*==============================================================================
* Function: Task6_500ms
* Description: 
*
==============================================================================*/
void Task6_500ms(void){
	/*Do nothing*/
}
