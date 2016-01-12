/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: Can_Manager.h $
 * $Revision: 1.0 $
 * $Author: Francisco Martinez
 * $Date: 16/08/2015 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file
*	File where the callback functions for the message buffers are allocated.
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
#ifndef __CAN_MANAGER
#define __CAN_MANAGER

/*============================================================================*/
/* Includes */
/*============================================================================*/
#include "Can.h"
#include "Cluster_EA.h"
/*============================================================================*/
/* Exported interfaces */
/*============================================================================*/
void CanManager_Receive_Fuel_Level (CAN_MessageDataType);
void CanManager_Receive_Odometer_Increment (CAN_MessageDataType);
void CanManager_Receive_Speed (CAN_MessageDataType);
void CanManager_Receive_Indicators_Status (CAN_MessageDataType);

/*============================================================================*/
#endif /* __CAN_MANAGER */
