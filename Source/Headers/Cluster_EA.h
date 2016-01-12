/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: Cluster_EA.h $
 * $Revision: 1.0 $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 12-01-2016 $
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
/*                     |      Cluster_EA    |           1.0                   */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: Cluster_EA.h  $
  ============================================================================*/
#ifndef CLUSTER_EA_H_
#define CLUSTER_EA_H_
/* Includes */
/*============================================================================*/
#include "GPIO_Manager.h"

/* Public functions */
/*============================================================================*/
void Update_speedometer (void);
void Update_fuel (void);
void Update_odometer(void);
void Update_indicators(void);

/* Global variables */
/*============================================================================*/
extern T_ULONG rul_odometer;
extern T_UWORD ruw_speed;
extern T_STRUCT_INDICATORS rs_indicators;
extern T_UWORD ruw_fuel_level;
extern T_UBYTE Reset_TRIP_ODO;
/*============================================================================*/
#endif /* CLUSTER_EA_H_ */
