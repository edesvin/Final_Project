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
 * $Date: 03-12-2015 $
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
/*                     |         LIN_EA      |         1.0                      */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: TASKS.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "TASKS.h"
#include "GPIO.h"
extern T_UBYTE blink_now;
/*==============================================================================
* Function: Task_
* Description: 
*
==============================================================================*/
void Task_10ms(void){
	Test();	
}
/*==============================================================================
* Function: Task_
* Description: 
*
==============================================================================*/
void Task_20ms(void){
#ifdef TRANSMITTER
	CanManager_SendMessage_12p5ms();
#endif
}
/*==============================================================================
* Function: Task_
* Description: 
*
==============================================================================*/
void Task_50ms(void){
#ifdef TRANSMITTER
	CanManager_SendMessage_25ms();
#endif
}
/*==============================================================================
* Function: Task_
* Description: 
*
==============================================================================*/
void Task_100ms(void){
#ifdef TRANSMITTER
	CanManager_SendMessage_100ms();
	#endif
}
