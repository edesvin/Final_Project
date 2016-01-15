#define M_CFLASH 0
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
#include "D_FLASH.h"

/*============================================================================*/
extern T_ULONG rul_odometer;
extern T_ULONG rul_trip_odometer;
T_ULONG rul_Count_Incremento = 0;
T_ULONG rul_Valid_Direction = START_ADDRESS;
/*==============================================================================
* Function: Init_CFLASH
* 
* Description: 
*
==============================================================================*/
void Init_DFLASH(void){
	
	DFLASH.LML.R = 0xA1A11111; /* write password */
	DFLASH.LML.R = 0x00100000; /* unlock low and mid blocks primary */
	DFLASH.SLL.R = 0xC3C33333; /* write password */
	DFLASH.SLL.R = 0x00100000; /* unlock low and mid blocks secondary */
	Set_Valid_Direction();
	Set_Odo_Values();
}
/*==============================================================================
* Function: FuncEraserFLASH
* 
* Description: 
*
==============================================================================*/
void Func_Erase_DFLASH(T_ULONG lub_Dir){
	
	DFLASH.MCR.B.ERS = 1;
	DFLASH.LMS.R = 0x0000000F; /* select B0F3 */
	*(T_ULONG *)lub_Dir = 0xFFFFFFFF; /* interlock write - write to any address in selected memory */
	DFLASH.MCR.B.EHV = 1;
	//Set_Pin_State( 68, !Get_Pin_StateOUT(68));
	while(!DFLASH.MCR.B.DONE){
		/* Do nothing*/
	}
	//Set_Pin_State( 69, !Get_Pin_StateOUT(69));
	DFLASH.MCR.B.EHV = 0;
	DFLASH.MCR.B.ERS = 0;
	
}
/*==============================================================================
* Function: FuncWriteFLASH
* 
* Description: 
*
==============================================================================*/
void Func_Write_DFLASH(T_ULONG lub_Dir, T_ULONG lub_Data_1, T_ULONG lub_Data_2){
	
	//Func_Erase_CFLASH(lub_Dir);
	
	DFLASH.MCR.B.PGM = 1; 
	*(T_ULONG *)lub_Dir = lub_Data_1; /* interlock write */
	*(T_ULONG *)(lub_Dir+4) = lub_Data_2; /* interlock write */
	DFLASH.MCR.B.EHV = 1;
	while(!DFLASH.MCR.B.DONE){
		/*Do nothing*/
	}
	DFLASH.MCR.B.EHV = 0;
	DFLASH.MCR.B.PGM = 0;
	
}
/*==============================================================================
* Function: Set_Valid_Direction
* 
* Description: 
*
==============================================================================*/
void Set_Valid_Direction(void){

	while((*((T_ULONG *)rul_Valid_Direction)) != 0xFFFFFFFF){
		rul_Valid_Direction += 4;
	}
	
}
/*==============================================================================
* Function: Set_Odo_Values
* 
* Description: 
*
==============================================================================*/
void Set_Odo_Values(void){
	if((*((T_ULONG *)(rul_Valid_Direction-8))) != 0xFFFFFFFF){
	  rul_odometer = (*((T_ULONG *)(rul_Valid_Direction-8)));
	}
	
	if((*((T_ULONG *)(rul_Valid_Direction - 4))) != 0xFFFFFFFF){
		  rul_trip_odometer = (*((T_ULONG *)(rul_Valid_Direction - 4)));
	}
}
/*==============================================================================
* Function: Check_Last_Address
* 
* Description: 
*
==============================================================================*/
void Check_Last_Address(void){
	
	if((*((T_ULONG *)FINAL_ADDRESS)) != 0xFFFFFFFF){
		
		Func_Erase_DFLASH(START_ADDRESS);
		rul_Valid_Direction = START_ADDRESS;
		rul_Count_Incremento = 0;
		
		Set_Valid_Direction();
	}
}
/*==============================================================================
* Function: Save_Data
* 
* Description: 
*
==============================================================================*/
void Save_Data(void){
	if((rul_Valid_Direction + (INCREMENT*rul_Count_Incremento))!=0xFFFFFFFF){
	  Func_Write_DFLASH((rul_Valid_Direction + (INCREMENT*rul_Count_Incremento)), rul_odometer, rul_trip_odometer);
	  rul_Count_Incremento++;
	}
	else{
		Func_Erase_DFLASH(START_ADDRESS);
		rul_Valid_Direction = START_ADDRESS;
		rul_Count_Incremento = 0;
	}
}

