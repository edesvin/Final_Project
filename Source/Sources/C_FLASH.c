/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: C_FLASH.c $
 * $Revision: 1.0 $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 07-01-2016 $
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
/*                     |     Cluster_EA     |            1.0                  */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: C_FLASH.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "C_FLASH.h"
/* Private functions */
/*============================================================================*/
void Func_Erase_CFLASH(T_ULONG);
/*==============================================================================
* Function: Init_CFLASH
* 
* Description: 
*
==============================================================================*/
void Init_CFLASH(void){
	
	CFLASH.LML.R = 0xA1A11111; /* write password */
	CFLASH.LML.R = 0x00100000; /* unlock low and mid blocks primary */
	CFLASH.SLL.R = 0xC3C33333; /* write password */
	CFLASH.SLL.R = 0x00100000; /* unlock low and mid blocks secondary */
	CFLASH.HBL.R = 0xB2B22222; /* write password */
	CFLASH.HBL.R = 0x00000000;  /* unlock high blocks */
	
}
/*==============================================================================
* Function: FuncEraserFLASH
* 
* Description: 
*
==============================================================================*/
void Func_Erase_CFLASH(T_ULONG lub_Dir){
	
	CFLASH.MCR.B.ERS = 1;
	CFLASH.LMS.R = 0x00000008; /* select B0F3 */
	*(T_ULONG *)lub_Dir = 0xFFFFFFFF; /* interlock write - write to any address in selected memory */
	CFLASH.MCR.B.EHV = 1;
	while(!CFLASH.MCR.B.DONE){
		/* Do nothing*/
	}
	CFLASH.MCR.B.EHV = 0;
	CFLASH.MCR.B.ERS = 0;

}
/*==============================================================================
* Function: FuncWriteFLASH
* 
* Description: 
*
==============================================================================*/
void Func_Write_CFLASH(T_ULONG lub_Dir, T_ULONG lub_Data){
	
	Func_Erase_CFLASH(lub_Dir);
	
	CFLASH.MCR.B.PGM = 1; 
	*(T_ULONG *)lub_Dir = lub_Data; /* interlock write */
	CFLASH.MCR.B.EHV = 1;
	while(!CFLASH.MCR.B.DONE){
		/*Do nothing*/
	}
	CFLASH.MCR.B.EHV = 0;
	CFLASH.MCR.B.PGM = 0;
	
}
/*=============================================================================*/
