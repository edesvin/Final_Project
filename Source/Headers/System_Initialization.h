/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: System_Initialization.h $
 * $Revision: 1.1 $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 12-01-2016 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file
    
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
 * $Log: System_Initialization.h  $
  ============================================================================*/
#ifndef SYSTEM_INITIALIZATION_H_
#define SYSTEM_INITIALIZATION_H_

/* Includes */
/*============================================================================*/
#include 	"TIMER.h"
#include    "GPIO.h"
#include 	"GPIO_Manager.h"
#include    "bspi.h"
#include    "Can.h"
#include    "Can_Cfg.h"
#include 	"Init_Tasks.h"
#include 	"Exceptions.h"
#include 	"IntcInterrupts.h"
#include	"LCD.h"
#include 	"ADC.h"
/* Public functions */
/*============================================================================*/
void System_Init(void);

#endif /* SYSTEM_INITIALIZATION_H_ */
