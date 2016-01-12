/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: Can_Manager.c $
 * $Revision: 1.0 $
 * $Author: Francisco Martinez
 * $Date: 16/08/2015 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file
*		File where the callback functions for the message buffers are allocated.
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
/*                     |     Cluster_EA     |         1.0                    */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: Can_Manager.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "Can_Manager.h"

/*==============================================================================
* Function: CanManager_Receive_Fuel_Level
* 
* Description: Function that receives the fuel level.
*
==============================================================================*/

void CanManager_Receive_Fuel_Level (CAN_MessageDataType CanMessage){
	if( CanMessage.msg_dlc_field == 2 ){
		ruw_fuel_level = CanMessage.msg_data_field[0] + (((T_UWORD)(CanMessage.msg_data_field[1]))<<8) & 0xFF00;
	}else{
		/* Do nothing */
	}
}
/*==============================================================================
* Function: CanManager_Receive_Odometer_Increment
* 
* Description: Function that receives the odometer increment.
*
==============================================================================*/

void CanManager_Receive_Odometer_Increment (CAN_MessageDataType CanMessage){
	if( CanMessage.msg_dlc_field == 1 ){
		rul_odometer += CanMessage.msg_data_field[0];
	}else{
		/* Do nothing */
	}
}
/*==============================================================================
* Function: CanManager_Receive_Speed
* 
* Description: Function that receives the speed.
*
==============================================================================*/
void CanManager_Receive_Speed (CAN_MessageDataType CanMessage){
	if( CanMessage.msg_dlc_field == 2 ){
		ruw_speed = CanMessage.msg_data_field[0] + (((T_UWORD)(CanMessage.msg_data_field[1]))<<8) & 0xFF00;
	}else{
		/* Do nothing */
	}
}

/*==============================================================================
* Function: CanManager_Receive_Indicators_Status
* 
* Description: Function that receives the state of the indicators.
*
==============================================================================*/
void CanManager_Receive_Indicators_Status (CAN_MessageDataType CanMessage){
	if( CanMessage.msg_dlc_field == 5 ){
		rs_indicators.Opened_Doors 		= CanMessage.msg_data_field[0];
		rs_indicators.Seat_Belt	 		= CanMessage.msg_data_field[1];
		rs_indicators.Fuel_Reserve		= CanMessage.msg_data_field[2];
		rs_indicators.High_Beams 		= CanMessage.msg_data_field[3];
		rs_indicators.Emergency_Break 	= CanMessage.msg_data_field[4];
	}else{
		/* Do nothing */
	}
}

