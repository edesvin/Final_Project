
/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: System_Initialization.c $
 * $Revision: 1.0 $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 06-12-2015 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/* The function of this module is to call the functions that initializes	  */
/* the mode of operation, peripherals, and the scheduler.					  */
    
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
/*                     |         	        |         1.0                      */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: System_Initialization.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "System_Initialization.h"

/* Private functions */
/*============================================================================*/
static void Mode_Entry(void);
/*==============================================================================
* Function: System_Init
* Description: This function calls the functions that initializes the mode 
* of operation, peripherals, and the scheduler.
*
==============================================================================*/
void System_Init(void){
	Mode_Entry();								 /* Mode and clock initializations 						*/
	InitPIT();									 /* PIT (Periodic Interrupt Timer) is initialized 		*/
	InitSTM(); 									 /* Timer STM is initialized 							*/
	Global_Init();								 /* The Scheduler is initialized						*/
	vfnGPIO_LED_Init();							 /* Initialize LEDs on TRK-MPC560xB board 				*/
	InitDSPI_1();								 /* SPI is initialized. The SBC is initialized by SPI 	*/
	ConfigureMZC33905DSPI_1();				 	 /* SBC  (System Basis Chip) configuration 				*/
	CAN_Initialization(&can_driver_config);		 /* CAN Initialization 									*/
	INTC_InitINTCInterrupts();					 /* Initialize Interrupts 								*/
	EXCEP_InitExceptionHandlers();				 /* Initialize Exception Handlers 						*/
	INTC_EnableInterrupts();					 /* Enable External Interrupts							*/
	LCDInit(LS_NONE);							 /* LCD initialization									*/
	LCDClear();									 /* The LCD is cleared									*/
}
/*==============================================================================
* Function: Mode_Entry
* Description: It initializes the mode of operation.
*
==============================================================================*/
static void Mode_Entry(void){
	ME.RUN[0].R = 0x001F0074;
	ME.RUNPC[0].R = 0x000000FE;
	ME.MCTL.R = 0x40005AF0;
	ME.MCTL.R = 0x4000A50F; 
}

