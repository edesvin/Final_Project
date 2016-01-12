#ifndef LCD_H
#define	LCD_H

/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: LCD.h $
 * $Revision: 1.2 $
 * &Project: Cluster_EA $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 11-01-2016 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file
*		This module configures and handles the state of the LCD.
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
/*                     |      Cluster_EA    |           1.2                   */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: LED.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "MPC5606B.h"
#include "typedefs.h"
#include "Timer.h"

#ifdef	__cplusplus
extern "C" {
#endif
/************************************************
	LCD CONNECTIONS
*************************************************/

#define LS_BLINK 0x01
#define LS_ULINE 0x02
#define LS_NONE	 0x00

/***************************************************
			F U N C T I O N S
****************************************************/

void LCDInit(T_UBYTE);
void LCDWriteString(const char *);
void LCDWriteInt(T_UBYTE, T_SBYTE);
void LCDGotoXY(T_UBYTE, T_UBYTE);
void LCDByte(T_UBYTE, T_UBYTE);

#define LCDCmd(c) (LCDByte(c,0))
#define LCDData(d) (LCDByte(d,1))



/***************************************************
			F U N C T I O N S     E N D
****************************************************/


/***************************************************
	M A C R O S
***************************************************/
#define LCDClear() LCDCmd(0x01)
#define LCDHome()  LCDCmd(0x02)

#define LCDWriteStringXY(x,y,msg) {\
 LCDGotoXY(x,y);\
 LCDWriteString(msg);\
}

#define LCDWriteIntXY(x,y,val,fl) {\
 LCDGotoXY(x,y);\
 LCDWriteInt(val,fl);\
}

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */	
