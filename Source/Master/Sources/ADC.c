/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: ADC.c $
 * $Revision: 1.0 $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 12-01-2016 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file
 *		This module handles the registers needed to configure the ADC 
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
/*                     |        Cluster_EA  |         1.0      		          */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: ADC.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "ADC.h"

/* Constants and types  */
/*============================================================================*/
#define  ADC0_P1            21	/*PCR for PB5*/
#define  ADC0_P2            22	/*PCR for PB6*/
#define  ADC0_P3            23	/*PCR for PB7*/
 
/* Exported functions */
/*============================================================================*/

 /*==============================================================================
 * Function: ADC_Config
 *
 * Description: Function that configures the pins for the ADC.
 *
 ==============================================================================*/
 void ADC_Config(void){
	 SIU.PCR[ADC0_P1].R = 0x2000; 			/* Configures the pin 1 as ADC	   */
	 SIU.PCR[ADC0_P2].R = 0x2000;			/* Configures the pin 2 as ADC	   */
	 SIU.PCR[ADC0_P3].R = 0x2000;			/* Configures the pin 3 as ADC	   */
 }
 
 /*==============================================================================
 * Function: ADCModeSelector
 *
 * Description: Function that selects the mode for the ADC.
 *
 ==============================================================================*/
 void ADCModeSelector(void){	
	 ADC_0.MCR.R = 0x20000000;				/* Chooses the mode : Scan mode		*/
	 ADC_0.NCMR0.R = 0x0E; 					/* Enable PChannels 1, 2, 3			*/
	 ADC_0.CTR0.R = 0x00008606;		
	 ADC_0.MCR.B.NSTART = 1;				/* Starts the conventions			*/
}

 /*==============================================================================
 * Function: Read_ADC
 *
 * Description: Function that gets the value of the ADC of the selected channel.
 *
 ==============================================================================*/
 T_UWORD Read_ADC(T_UBYTE lub_Channel){
	 T_UWORD luw_AdcValue = 0;
	 luw_AdcValue = (T_UWORD)(ADC_0.CDR[lub_Channel].B.CDATA);	/* Read ADC pin */
	 return luw_AdcValue;
 }
 

