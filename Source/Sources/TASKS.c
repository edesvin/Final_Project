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

extern T_UBYTE ruw_Display_Number1;
extern T_UBYTE ruw_Display_Number2;
extern T_UBYTE ruw_Display_Number3;

/*==============================================================================
* Function: Task0_5ms
* Description: 
*
==============================================================================*/
void Task0_3ms(void){
	/* Debounce  */
}

/*==============================================================================
* Function: Task1_10ms
* Description: 
*
==============================================================================*/
void Task1_5ms(void){
	
	Update_speedometer();
	
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
	
/*	if(ruw_Display_Number1++ >= 9){
		ruw_Display_Number1 = 0;
		if(ruw_Display_Number2++ >= 9){
			ruw_Display_Number2 = 0;
			if(ruw_Display_Number3++ >= 9) ruw_Display_Number3 = 0;
		}
	}*/
	
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
	 Update_fuel();  
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
	Update_odometer();   
}

/*==============================================================================
* Function: Task5_250ms
* Description: 
*
==============================================================================*/
void Task5_250ms(void){
	
	/* Get_switches_State();*/
	 Update_indicators(); 
}
