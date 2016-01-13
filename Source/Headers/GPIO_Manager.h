/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: GPIO_Manager.h $
 * $Revision: 1.0 $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 11-01-2016 $
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
/*                     |     Cluster_EA     |           1.0                   */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: GPIO_Manager.h  $
  ============================================================================*/
#ifndef GPIO_MANAGER_H_
#define GPIO_MANAGER_H_
/* Includes */
/*============================================================================*/
#include "GPIO.h"
#include "stdtypedef.h"

#define PORTA 0		//7 segment display
#define PORTG 96	//indicator led
#define PORTF 80	//LCD
#define PORTD 48	//led-bar

#define BOARD_LEDS 68

#define LCD_E	84
#define LCD_RW	85
#define LCD_RS	86

#define SET		1
#define RESET	0

#define PIN_LCD_DATA_0	80
#define PIN_LCD_DATA_1	81
#define PIN_LCD_DATA_2	82
#define PIN_LCD_DATA_3	83

#define LED_OPENED_DOOR 	100
#define LED_SEAT_BELT 		99
#define LED_HIGH_BEAMS 		98
#define LED_EMERGENCY_BREAK 97
#define LED_RESERVE			96

typedef struct{
	T_UBYTE Opened_Doors	: 1;
	T_UBYTE Seat_Belt	 	: 1;
	T_UBYTE Fuel_Reserve	: 1;
	T_UBYTE High_Beams 	 	: 1;
	T_UBYTE Emergency_Break : 1;
	
}T_STRUCT_INDICATORS;
/* Public functions */
/*============================================================================*/
void Init_GPIO (void);

void Set_LCD_Data_Output(void);
void Set_LCD_Data_Input(void);
void Set_LCD_E(T_UBYTE State);
void Set_LCD_RW(T_UBYTE State);
void Set_LCD_RS(T_UBYTE State);
T_UBYTE Read_LCD_Data(void);
void Set_LCD_Data(T_UBYTE Data_Pin,T_UBYTE State);

void Display_Speed(T_UWORD);
void Data_Module(T_UWORD);
void Set_Transistors(T_UBYTE);
void Print_Display_Number(T_UBYTE);

void Set_Indicator(T_STRUCT_INDICATORS, T_UWORD);

void Set_Bar_Led(T_UBYTE);
void Set_Reserve_Led(void);
		
#endif /* GPIO_MANAGER_H_ */
