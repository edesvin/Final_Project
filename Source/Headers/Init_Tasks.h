/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: Init_Tasks.h $
 * $Revision: 1.1 $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 07-01-2016 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file
		This file contains the type definitions and the prototypes for the 
		functions used to initialize the software.
	
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
/*                     |     Cluster_EA     |           1.1                   */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: Init_Tasks.h  $
  ============================================================================*/
#ifndef INIT_TASKS_H_
#define INIT_TASKS_H_
/* Includes */
/*============================================================================*/
#include "TASKS.h"
#include "stdtypedef.h"
/* Constants and types */
/*============================================================================*/
typedef enum{
	
	E_TSK_TASK0,
	E_TSK_TASK1,
	E_TSK_TASK2,
	E_TSK_TASK3,
	E_TSK_TASK4,
	E_TSK_TASK5,
	/*Write here your new tasks*/
	
	E_TSK_N_OF
	
}E_TASKS;
/*============================================================================*/
typedef struct{
	
	void(*F_Pointer)(void);		/*	Function Pointer	*/	
	T_UWORD uw_T;				/* 	Period				*/
	T_UWORD uw_Offset;			/*	Offset				*/
	
}S_STAT;

/* Public functions */
/*============================================================================*/
extern void Global_Init(void);

#endif /* INIT_TASKS_H_ */
