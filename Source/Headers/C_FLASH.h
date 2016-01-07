/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: C_FLASH.h $
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
 * $Log: C_FLASH.h  $
  ============================================================================*/
#ifndef C_FLASH_H_
#define C_FLASH_H_
/* Includes */
/*============================================================================*/
#include "MPC5606B.h"
#include "stdtypedef.h"
/*============================================================================*/
#define DIRECTION_1 0x00010000
#define DATA_0 0
#define DATA_1 1

/* Public functions */
/*============================================================================*/
void Init_CFLASH(void);
void Func_Write_CFLASH(T_ULONG, T_ULONG);

#endif /* C_FLASH_H_ */
