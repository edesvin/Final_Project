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
#include "ADC.h"

uint8_t msg0_speed[8]		  = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t msg1_odo_increment[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t msg2_fuel_level[8]	  = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
uint8_t msg3_indicators[8]	  = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

CAN_PduType    pdu_handler0_speed 			= { 1, 2, msg0_speed};
CAN_PduType    pdu_handler1_odo_increment 	= { 2, 1, msg1_odo_increment};
CAN_PduType    pdu_handler2_fuel_level 		= { 5, 2, msg2_fuel_level};
CAN_PduType    pdu_handler3_indicators		= { 6, 4, msg3_indicators};

/*==============================================================================
* Function: CanManager_Send_Speed
* 
* Description:
*
==============================================================================*/
void CanManager_Send_Speed(void){
	T_UWORD ADC_Value = (T_UWORD)((((T_ULONG)Read_ADC(1))*2000)/93);
	msg0_speed[0] = (T_UBYTE)( ADC_Value & 0x00FF );
	msg0_speed[1] = (T_UBYTE)( ADC_Value >> 8 );
	pdu_handler0_speed.can_sdu = msg0_speed;
	CAN_SendFrame(&pdu_handler0_speed);
}

/*==============================================================================
* Function: CanManager_Send_Odometer_Increment
* 
* Description:
*
==============================================================================*/
void CanManager_Send_Odometer_Increment(void){
	static T_UWORD meters_odometer = 0;
	T_UWORD ADC_Value = (T_UWORD)((((T_ULONG)Read_ADC(1))*25)/1674);
	
	meters_odometer += ADC_Value;
	
	if(meters_odometer >= 100){
		msg1_odo_increment[0] = (T_UBYTE) (meters_odometer / 100);
		meters_odometer -= (msg1_odo_increment[0]*100);
		pdu_handler1_odo_increment.can_sdu = msg1_odo_increment;
		CAN_SendFrame(&pdu_handler1_odo_increment);
	}
	
	
}
/*==============================================================================
* Function: CanManager_Send_Fuel_Level
* 
* Description:
*
==============================================================================*/

void CanManager_Send_Fuel_Level(void){
	T_UWORD ADC_Value = (T_UWORD)((((T_ULONG)Read_ADC(2))*500)/1023);
	msg2_fuel_level[0] = (T_UBYTE)( ADC_Value & 0x00FF );	
	msg2_fuel_level[1] = (T_UBYTE)( ADC_Value >> 8 );
	pdu_handler2_fuel_level.can_sdu = msg2_fuel_level;
	CAN_SendFrame(&pdu_handler2_fuel_level);
}
/*==============================================================================
* Function: 
* 
* Description:
*
==============================================================================*/

void CanManager_Send_Indicators(void){
	
	msg3_indicators[0] = rs_indicators.Opened_Doors;
	msg3_indicators[1] = rs_indicators.Seat_Belt;	
	msg3_indicators[2] = rs_indicators.High_Beams;
	msg3_indicators[3] = rs_indicators.Emergency_Break;
	
	pdu_handler3_indicators.can_sdu = msg3_indicators;
	CAN_SendFrame(&pdu_handler3_indicators);
}

