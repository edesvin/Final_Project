/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: TASKS.h $
 * $Revision: 1.1 $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 07-01-2016 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file
    Prototypes of the functions that contain the tasks.
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
 * $Log: TASKS.h  $
  ============================================================================*/
#ifndef TASKS_H_
#define TASKS_H_
/* Includes */
/*============================================================================*/
#include "typedefs.h"
#include "Can_Manager.h"
#include "GPIO_Manager.h"
#include "D_FLASH.h"
/* Exported functions prototypes */
/*============================================================================*/
extern void Task0_3ms(void);
extern void Task1_5ms(void);
extern void Task2_50ms(void);
extern void Task3_100ms(void);
extern void Task4_200ms(void);
extern void Task5_250ms(void);
extern void Task5_1000ms(void);
/*Add here the prototype of your new task*/

#endif /* TASKS_H_ */
