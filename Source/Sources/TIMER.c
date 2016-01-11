/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: TIMER.c $
 * $Revision: 1.1 $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 11-01-2016 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file
*	This file contains the configurations that must be done to achieve the 
*	periodic interrupt that gives the Ticks to the scheduler.
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
/*                     |     Cluster_EA     |         1.1                     */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: TIMER.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "TIMER.h"
/* Defines */
/*============================================================================*/
#define LDVAL_0			0x0000F9FF		/*	Timer Start Value */
#define ISR_PIT_CH0 	59
#define PRIORITY_5 		5
#define CHANNEL_0		0
#define STM_VALUE 		STM.CNT.R
#define CLEAR 			0x00
/* Private functions */
/*============================================================================*/
static void InitPITChannel (T_UBYTE);

/*==============================================================================
* Function: 
* 
* Description: 
*
==============================================================================*/
void InitSTM(void){
	STM.CR.B.CPS = 0x00;			/* Preescaler value = 1 			*/
	STM.CR.B.FRZ = 0x00; 			/* Disable debug mode for timer.	*/
	STM.CR.B.TEN = 0x01; 			/* Enable STM timer.				*/
}

/*==============================================================================
* Function: 
* 
* Description: 
*
==============================================================================*/
void Clear_STM(void){
	STM_VALUE = CLEAR;
}
/*==============================================================================
* Function: InitPIT
* 
* Description: PIT is initialized.
*
==============================================================================*/
void InitPIT (void){
	
	PIT.PITMCR.B.MDIS = 0;													/* Clock for PIT timers is enabled.		*/
	PIT.PITMCR.B.FRZ = 1;													/* Timers are stopped in debug mode. 	*/
	INTC_InstallINTCInterruptHandler( Tick_ISR, ISR_PIT_CH0, PRIORITY_5 );	/* Software Interrupt					*/
	INTC.CPR.R = 0;
	InitPITChannel(CHANNEL_0);
	
}
/*==============================================================================
* Function: InitPITChannel
* 
* Description: This function configures the given channel of the PIT timer.
*
==============================================================================*/
void InitPITChannel (T_UBYTE lub_CH ) {
	
	PIT.CH[lub_CH].LDVAL.R = LDVAL_0;	/* Time Start Value.									 */
	PIT.CH[lub_CH].TCTRL.B.TEN = 1;		/* Timer will be active.								 */
	PIT.CH[lub_CH].TCTRL.B.TIE = 1;		/* Interrupt will be requested whenever TIF is set.		 */
	PIT.CH[lub_CH].TFLG.B.TIF = 1;		/* Time Interrupt Flag.									 */
		
}
