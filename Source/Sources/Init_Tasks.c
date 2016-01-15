/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: Init_Tasks.c $
 * $Revision: 1.1 $
 * $Author:		Edgar Escayola Vinagre	$
 *		 		Adrian Zacarias Siete	$
 *			
 * $Date: 07-01-2015 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \Init_Tasks.c

		This file contains the global initializations for the Scheduler
		
		It contains the array that has the description of the tasks: 
		function pointers, periods and offsets. Also the software initializations.
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
/*                     |      Cluster_EA    |           1.1                   */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: Init_Tasks.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "Init_Tasks.h"

/* Public variables */
/*============================================================================*/
volatile T_UWORD raub_DynConuter[E_TSK_N_OF];

const S_STAT cas_STAT[E_TSK_N_OF] = {/*	Function Pointer	-	Period 	-	  Offset	*/
		
		{		&Task0_3ms,					3	,		0		},
		{		&Task1_5ms,					5	,		1		},
		{		&Task2_50ms,				50	,		2		},
		{		&Task3_100ms,				100	,		3		},
		{		&Task4_200ms,				200	,		5		},
		{		&Task5_250ms,				250	,		7		},
		{		&Task5_1000ms,				1000,		8		},
		/*	Add here your new task and a comma before the last one	*/			
		/*	{	Function Pointer	,	Period	,		Offset	}	*/	
};
/*==============================================================================
* Function: Global_Init
*
* Description: This function initializes the scheduler.
*
==============================================================================*/
void Global_Init(void){

	T_UWORD luw_i;

	for(luw_i = 0; luw_i < E_TSK_N_OF; luw_i++){
		raub_DynConuter[luw_i] = cas_STAT[luw_i].uw_Offset;
	}
}
