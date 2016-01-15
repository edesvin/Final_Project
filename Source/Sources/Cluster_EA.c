/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: Cluster_EA.c $
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
/*                     |     Cluster_EA     |         1.0                    */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: Cluster_EA.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "Cluster_EA.h"
/* Defines */
/*============================================================================*/


/* Global variables */
/*============================================================================*/
T_ULONG rul_trip_odometer = 50;
T_ULONG rul_odometer = 200;
T_UWORD ruw_speed = 0;
T_STRUCT_INDICATORS rs_indicators = {0,0,0,0,0};
T_UWORD ruw_fuel_level;
T_UBYTE Reset_TRIP_ODO;

/* Private functions */
/*============================================================================*/
void Reset_Debounce (void);
T_UBYTE F_Full_State (T_UBYTE);
T_UBYTE F_3_4_State (T_UBYTE);
T_UBYTE F_1_2_State (T_UBYTE);
T_UBYTE F_1_4_State (T_UBYTE);
T_UBYTE F_Reserve_State (T_UBYTE);
T_UBYTE F_Minimum_State(T_UBYTE);
T_UBYTE F_Empty_State (T_UBYTE);
void Init_Gas_State (void);
T_UBYTE D_Opened_State (T_UBYTE);
T_UBYTE D_Closed_State (T_UBYTE);
T_UBYTE SB_Off_State (T_UBYTE);
T_UBYTE SB_Blinking_State (T_UBYTE);
T_UBYTE SB_On_State (T_UBYTE);
T_UBYTE HB_Off_State (T_UBYTE);
T_UBYTE HB_On_State (T_UBYTE);
T_UBYTE EB_Active_State (T_UBYTE);
T_UBYTE EB_Inactive_State (T_UBYTE);

extern T_UBYTE rub_Unit_Selector_Validation_Flag;
extern T_UBYTE rub_Reset_Validation_Flag;

/*==============================================================================
* Function: Reset_Debounce
* 
* Description:
*
==============================================================================*/
void Reset_Debounce(void){	  
	if(rub_Reset_Validation_Flag == TRUE){
		rul_trip_odometer = 0;
		rub_Reset_Validation_Flag = FALSE;
	}
}
/*==============================================================================
* Function: Debounce
* 
* Description:
*
==============================================================================*/

void Debounce (void){
	
	Reset_Debounce();
	Push_Button_State();

}
/*==============================================================================
* Function: Update_speedometer
* 
* Description: Function that updates the speedometer.
*
==============================================================================*/
void Update_Displays (void){
	
	Display_Speed();
}

/*==============================================================================
* Function: Update_fuel 
* 
* Description: Function that updates the fuel level.
*
==============================================================================*/
void Update_fuel (void){
	
	static T_UBYTE lub_State_Fuel_Level = 6;
	
	//LCDWriteIntXY( 15, 3, ruw_fuel_level, 3 );

	switch(lub_State_Fuel_Level){
	case 0:
		lub_State_Fuel_Level = F_Full_State(lub_State_Fuel_Level);
		break;
	case 1:
		lub_State_Fuel_Level = F_3_4_State(lub_State_Fuel_Level);
		break;
	case 2:
		lub_State_Fuel_Level = F_1_2_State(lub_State_Fuel_Level);
		break;
	case 3:
		lub_State_Fuel_Level = F_1_4_State(lub_State_Fuel_Level);
		break;
	case 4:
		lub_State_Fuel_Level = F_Minimum_State(lub_State_Fuel_Level);
		break;
	case 5:
		lub_State_Fuel_Level = F_Reserve_State(lub_State_Fuel_Level);
		break;
	case 6:
		lub_State_Fuel_Level = F_Empty_State(lub_State_Fuel_Level);
		break;
	default:
		break;
	}
	
}

/*==============================================================================
* Function:  Update_odometer
* 
* Description: Function that updates the value of the odometer.
*
==============================================================================*/
void Update_odometer(void){
	
	LCDWriteIntXY( 7, 1, rul_odometer / 10, 6 );
	LCDWriteIntXY( 7, 2, rul_trip_odometer / 10, 4 );
	LCDWriteIntXY( 12, 2, rul_trip_odometer % 10, 1 );

}

/*==============================================================================
* Function: Update_indicators
* 
* Description: Function that update the state of the indicators.
*
==============================================================================*/
void Update_indicators(void){
	
	Set_Indicator(rs_indicators, ruw_speed);
	
}

/*==============================================================================
* Function: F_Full_State
* 
* Description: Fuel gauge full state.
*
==============================================================================*/
T_UBYTE F_Full_State (T_UBYTE lub_Data){
	Set_Bar_Led(5);
	return Set_State(lub_Data);
}

/*==============================================================================
* Function: F_3_4_State
* 
* Description: Fuel gauge three quarters state.
*
==============================================================================*/
T_UBYTE F_3_4_State (T_UBYTE lub_Data){
	Set_Bar_Led(4);
	return Set_State(lub_Data);
}

/*==============================================================================
* Function: F_1_2_State
* 
* Description: Fuel gauge half state.
*
==============================================================================*/
T_UBYTE F_1_2_State (T_UBYTE lub_Data){
	Set_Bar_Led(3);
	return Set_State(lub_Data);
}

/*==============================================================================
* Function: F_1_4_State
* 
* Description: Fuel gauge one quarter state.
*
==============================================================================*/
T_UBYTE F_1_4_State (T_UBYTE lub_Data){
	Set_Bar_Led(2);
	return Set_State(lub_Data);
}

/*==============================================================================
* Function: F_Reserve_State
* 
* Description: Fuel gauge reserve state.
*
==============================================================================*/
T_UBYTE F_Reserve_State (T_UBYTE lub_Data){
	Set_Bar_Led(1);
	Set_Reserve_Led();
	return Set_State(lub_Data);
}

/*==============================================================================
* Function: F_Empty_State
* 
* Description: Fuel gauge empty state.
*
==============================================================================*/
T_UBYTE F_Empty_State (T_UBYTE lub_Data){
	Set_Bar_Led(0);
	return Set_State(lub_Data);
}
/*==============================================================================
* Function: F_Minimum_State
* 
* Description: Fuel gauge empty state.
*
==============================================================================*/
T_UBYTE F_Minimum_State(T_UBYTE lub_Data){
	Set_Bar_Led(1);
	return Set_State(lub_Data);
}
/*==============================================================================
* Function: Init_Gas_State
* 
* Description: Function that handles the 4 seconds initialization of the fuel gauge.
*
==============================================================================*/
void Init_Gas_State (void){

}

/*==============================================================================
* Function: D_Opened_State
* 
* Description: Doors opened state
*
==============================================================================*/
T_UBYTE D_Opened_State (T_UBYTE){

}

/*==============================================================================
* Function: D_Closed_State
* 
* Description: Doors closed state.
*
==============================================================================*/
T_UBYTE D_Closed_State (T_UBYTE){

}

/*==============================================================================
* Function: SB_Off_State
* 
* Description: Seat belt off state.
*
==============================================================================*/
T_UBYTE SB_Off_State (T_UBYTE){

}

/*==============================================================================
* Function: SB_Blinking_State
* 
* Description: Seat belt blinking state.
*
==============================================================================*/
T_UBYTE SB_Blinking_State (T_UBYTE){

}

/*==============================================================================
* Function: SB_On_State
* 
* Description: Seat belt on state.
*
==============================================================================*/
T_UBYTE SB_On_State (T_UBYTE){

}

/*==============================================================================
* Function: HB_Off_State
* 
* Description: High beams off state.
*
==============================================================================*/
T_UBYTE HB_Off_State (T_UBYTE){

}

/*==============================================================================
* Function: HB_On_State
* 
* Description: High beams on state.
*
==============================================================================*/
T_UBYTE HB_On_State (T_UBYTE){

}

/*==============================================================================
* Function: EB_Active_State
* 
* Description: Emergency break active state.
*
==============================================================================*/
T_UBYTE EB_Active_State (T_UBYTE){

}

/*==============================================================================
* Function: EB_Inactive_State
* 
* Description: Emergency break inactive state.
*
==============================================================================*/
T_UBYTE EB_Inactive_State (T_UBYTE){

}
/*==============================================================================
* Function: Set_State
* 
* Description:
*
==============================================================================*/
T_UBYTE Set_State(T_UBYTE lub_State){
	if(ruw_fuel_level >= 400){
		lub_State = 0;
	}
	else if(ruw_fuel_level >= 300){
		lub_State = 1;
	}
	else if(ruw_fuel_level >= 200){
		lub_State = 2;
	}
	else if(ruw_fuel_level >= 100){
		lub_State = 3;
	}
	else if(ruw_fuel_level >= 62){
		lub_State = 4;
	}
	else if(ruw_fuel_level >= 5){
		lub_State = 5;
	}
	else{
		lub_State = 6;
	}
	return lub_State;
}
/*==============================================================================
* Function: Update_speedometer
* 
* Description:
*
==============================================================================*/
void Update_speedometer(void){
	Data_Module(ruw_speed);
}

