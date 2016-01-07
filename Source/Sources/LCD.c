/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: LCD.c $
 * $Revision: 1.0 $
 * &Project: Cluster_EA $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 07-01-2016 $
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
/*                   			 HISTORY            				          */
/*============================================================================*/
/* Revision |   Date   |    Author      | Description		       			  */
/*----------------------------------------------------------------------------*/
/*    1.0   | 07/01/16 | Edgar Escayola | Creation of the file		          */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*
 * $Log: LED.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "LCD.h"

#define LCD_DATA_0 			SIU.GPDO[80].B.PDO
#define LCD_DATA_1 			SIU.GPDO[81].B.PDO 
#define LCD_DATA_2 			SIU.GPDO[82].B.PDO 
#define LCD_DATA_3 			SIU.GPDO[83].B.PDO

#define LCD_DATA_STATE_0 	SIU.GPDI[80].B.PDI
#define LCD_DATA_STATE_1 	SIU.GPDI[81].B.PDI
#define LCD_DATA_STATE_2 	SIU.GPDI[82].B.PDI 
#define LCD_DATA_STATE_3 	SIU.GPDI[83].B.PDI 

#define LCD_DATA_TRIS_0 	SIU.PCR[80].R
#define LCD_DATA_TRIS_1 	SIU.PCR[81].R
#define LCD_DATA_TRIS_2 	SIU.PCR[82].R
#define LCD_DATA_TRIS_3 	SIU.PCR[83].R

#define LCD_RS         		SIU.GPDO[84].B.PDO
#define LCD_RS_TRIS    		SIU.PCR[84].R

#define LCD_RW          	SIU.GPDO[85].B.PDO
#define LCD_RW_TRIS     	SIU.PCR[85].R

#define LCD_E           	SIU.GPDO[86].B.PDO
#define LCD_E_TRIS      	SIU.PCR[86].R

#define SET_E() 			(LCD_E = 1)
#define SET_RS() 			(LCD_RS = 1)
#define SET_RW() 			(LCD_RW = 1)

#define CLEAR_E() 			(LCD_E = 0)
#define CLEAR_RS() 			(LCD_RS = 0)
#define CLEAR_RW() 			(LCD_RW = 0)

#define OUTPUT				 0x0200
#define INPUT 				 0x0100
#define CLEAR 				 0x0000;

#define SET_CUSTOM_CHARS			0x40
#define DISPLAY_ON					0x0C
#define FOUR_BIT_TWO_LINE_FORMAT 	0x28
#define FOUR_BIT_MODE 				0x01
#define FIRST_BIT					0x01
#define SECOND_BIT					0x02
#define THIRD_BIT					0x04
#define FOURTH_BIT					0x08
#define MASK_LOW_HALF_BYTE			0x0F
#define MASK_0X80					0x80
#define FIRST_LINE					0x80
#define SECOND_LINE 				0x40
#define THIRD_LINE					0x14
#define FOURTH_LINE					0x54
#define MAX_X_VALUE					20

void delay_1u(void);
void delay_500n(void);
void delay_30ms(void);

void initSTM(void){
	STM.CR.B.CPS = 0x00;			/* Preescaler value = 1 			*/
	STM.CR.B.FRZ = 0x00; 			/* Disable debug mode for timer.	*/
	STM.CR.B.TEN = 0x01; 			/* Enable STM timer.				*/
}

void delay_1u(void){
	STM.CNT.R = 0;					/* Reset STM counter */	
	while( STM.CNT.R <= 64 ){
		/* Wait for 1 us */
	}
}

void delay_500n(void){
	STM.CNT.R = 0;					/* Reset STM counter */	
	while( STM.CNT.R <= 32 ){
		/* Wait for 500 ns */
	}
}

void delay_30ms(void){
	STM.CNT.R = 0;					/* Reset STM counter */	
	while( STM.CNT.R <= 0x1D4C00 ){
		/* Wait for 30 ms */
	}
}
void LCDByte(T_UBYTE lub_byte, T_UBYTE lub_isdata)
{
    //Sends a byte to the LCD in 4bit mode
    //cmd=0 for data
    //cmd=1 for command

    T_UBYTE lub_high_byte, lub_low_byte;		
    T_UBYTE lub_temp;

    lub_high_byte = lub_byte >> 4; 		/* Divide the byte that will be sent in 4 byte mode */	
    lub_low_byte = lub_byte & 0x0F;

    if(lub_isdata == 0){				/* Check whether it is a command */	
		CLEAR_RS();
    }else{
		SET_RS();
	}
	
    delay_500n();		

    SET_E();

    lub_temp = ( ( LCD_DATA_STATE_0 +  (LCD_DATA_STATE_1<<1) + (LCD_DATA_STATE_2<<2) +  (LCD_DATA_STATE_3<<3)) & (~(0X0F)))|(lub_high_byte);
    LCD_DATA_0 = lub_temp & FIRST_BIT;
	LCD_DATA_1 = ((lub_temp & SECOND_BIT) >> 1) & FIRST_BIT;
    LCD_DATA_2 = ((lub_temp & THIRD_BIT)  >> 2) & FIRST_BIT;
	LCD_DATA_3 = ((lub_temp & FOURTH_BIT) >> 3) & FIRST_BIT;
	
    delay_1u();			
    
    CLEAR_E(); 	/* Now that the data lines are stable, E is pulled low for transmission */

    delay_1u();

    SET_E(); 	/* Send the lower nibble */

    lub_temp = ( (LCD_DATA_STATE_0 +  (LCD_DATA_STATE_1<<1) + (LCD_DATA_STATE_2<<2) +  (LCD_DATA_STATE_3<<3)) & (~(0X0F)))|(lub_low_byte);
    LCD_DATA_0 = lub_temp & FIRST_BIT;
	LCD_DATA_1 = ((lub_temp & SECOND_BIT) >> 1) & FIRST_BIT;
    LCD_DATA_2 = ((lub_temp & THIRD_BIT)  >> 2) & FIRST_BIT;
	LCD_DATA_3 = ((lub_temp & FOURTH_BIT) >> 3) & FIRST_BIT;

    delay_1u();			

    CLEAR_E(); /* The transmission of the lower nibble is done */

    delay_1u();		

    LCDBusyLoop(); /* Check whether the LCD is Busy */
    
}

void LCDBusyLoop(){
	
    T_UBYTE lub_temp, lub_busy, lub_status;

    /* Set Data lines as INPUT */
	LCD_DATA_TRIS_0 = INPUT;
	LCD_DATA_TRIS_1 = INPUT;
	LCD_DATA_TRIS_2 = INPUT;
	LCD_DATA_TRIS_3 = INPUT;
	
    /* Change LCD mode */
    SET_RW();		/* Read mode */
    CLEAR_RS();		/* Read status */

    /*Let the RW/RS lines stabilize */
    delay_500n();	
    
	do{
		SET_E();

		
		delay_500n();	 /* Wait for data to become available */

		lub_status = ( LCD_DATA_STATE_0 ) +  ( LCD_DATA_STATE_1<<1 ) + ( LCD_DATA_STATE_2<<2 ) +  ( LCD_DATA_STATE_3<<3 );
		lub_status = lub_status<<4;

		delay_500n();	

		CLEAR_E();
		delay_1u();

		SET_E();
		delay_500n();	

		lub_temp = ( LCD_DATA_STATE_0 ) +  ( LCD_DATA_STATE_1<<1 ) + ( LCD_DATA_STATE_2<<2 ) +  ( LCD_DATA_STATE_3<<3 );
		lub_temp &= MASK_LOW_HALF_BYTE;

		lub_status = lub_status | lub_temp;

		lub_busy = lub_status & MASK_0X80;

		delay_500n();	

		CLEAR_E();
		delay_1u();
			
    }while(lub_busy);

    CLEAR_RW();		/* Write mode */

	/* Set Data lines as OUTPUTS */
	LCD_DATA_TRIS_0 = OUTPUT;
	LCD_DATA_TRIS_1 = OUTPUT;
	LCD_DATA_TRIS_2 = OUTPUT;
	LCD_DATA_TRIS_3 = OUTPUT;
	
}

void LCDInit(T_UBYTE lub_style){
	
	/*****************************************************************

	This function Initializes the lcd module
	must be called before calling lcd related functions

	Arguments:
	style = LS_BLINK,LS_ULINE(can be "OR"ed for combination)
	LS_BLINK : The cursor is blinking type
	LS_ULINE : Cursor is "underline" type else "block" type
        LS_NONE : No visible cursor

	*****************************************************************/

	T_UBYTE lub_i;

	T_UBYTE lub_custom_char[]=
	{
		0x0C, 0x12, 0x12, 0x0C, 0x00, 0x00, 0x00, 0x00, //Char0 degree symbol
		0x01, 0x07, 0x1F, 0x1F, 0x1F, 0x1F, 0x19, 0x00, //Char1 
		0x1F, 0x00, 0x0E, 0x0E, 0x0E, 0x00, 0x1F, 0x00, //Char2
		0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, //Char3
		0x03, 0x02, 0x0E, 0x0A, 0x0E, 0x02, 0x03, 0x00, //Char4
		0x10, 0x1C, 0x1F, 0x1F, 0x1F, 0x1F, 0x13, 0x00, //Char5 -
		0x03, 0x06, 0x0E, 0x0F, 0x1E, 0x1C, 0x19, 0x1A, //Char6 s
		0x18, 0x0C, 0x0E, 0x1E, 0x0F, 0x17, 0x03, 0x03, //Char7
		//0x1C, 0x1B, 0x1C, 0x0D, 0x0D, 0x0D, 0x07, 0x03, //Char8
	//	0x07, 0x13, 0x0F, 0x16, 0x16, 0x16, 0x1C, 0x18, //Char9
	};
        
	

	delay_30ms(); /* After power on Wait for LCD to Initialize */
	
	/* Set Data lines as OUTPUTS */
	LCD_DATA_TRIS_0 = OUTPUT;
	LCD_DATA_TRIS_1 = OUTPUT;
	LCD_DATA_TRIS_2 = OUTPUT;
	LCD_DATA_TRIS_3 = OUTPUT;

	/* Set control lines as OUTPUTS */
	LCD_E_TRIS  = OUTPUT;   
	LCD_RS_TRIS = OUTPUT; 
	LCD_RW_TRIS = OUTPUT;  

	/* Clear all the lines */
	LCD_DATA_0 = CLEAR;
	LCD_DATA_1 = CLEAR;
	LCD_DATA_2 = CLEAR;
	LCD_DATA_3 = CLEAR;
	
    CLEAR_E();
	CLEAR_RW();
	CLEAR_RS();
	
	delay_500n();

	SET_E();
	LCD_DATA_1 = FOUR_BIT_MODE;  /* Set 4-bit mode */
	delay_1u();
	CLEAR_E();
	delay_1u();

	
	LCDBusyLoop(); /* Wait for LCD */ 

	/* Now the LCD is in 4-bit mode */

	LCDCmd(FOUR_BIT_TWO_LINE_FORMAT); /* Function set 4-bit, 2 line 5x7 dot format  */
    LCDCmd(DISPLAY_ON | lub_style);	  /* Display On									*/

	/* Custom Char */
    LCDCmd(SET_CUSTOM_CHARS);


	for(lub_i=0; lub_i<sizeof(lub_custom_char); lub_i++){
		LCDData(lub_custom_char[lub_i]);
	}

}
void LCDWriteString(const char *msg)
{
	/*****************************************************************

	This function Writes a given string to lcd at the current cursor
	location.

	Arguments:
	msg: a null terminated C style string to print

	There are 8 custom char in the LCD they can be defined using
	"LCD Custom Character Builder" PC Software.

	You can print custom character using the % symbol. For example
	to print custom char number 0 (which is a degree symbol), you
	need to write

	LCDWriteString("Temp is 30%0C");
                                  ^^
                                   |----> %0 will be replaced by
                                          custom char 0.

	So it will be printed like.

		Temp is 30°C

	In the same way you can insert any symbols numbered 0-7


	*****************************************************************/
	T_UBYTE lub_cc_support;
	
	while(*msg!='\0'){
		if(*msg=='%'){ 	/*Custom Char Support */
			msg++;
			lub_cc_support = (T_UBYTE)(*msg-'0');
		
			if( lub_cc_support>=0 && lub_cc_support<=7 ){
				LCDData(lub_cc_support);
			}else{
				LCDData('%');
				LCDData(*msg);
			}
		}else{
			LCDData(*msg);
		}
		msg++;
	}
}

void LCDWriteInt(T_UBYTE lub_val, T_SBYTE lsb_field_length){
	
	/***************************************************************
	This function writes a integer type value to LCD module

	Arguments:
	1)int val	: Value to print

	2)unsigned int field_length :total length of field in which the value is printed
	must be between 1-5 if it is -1 the field length is no of digits in the val

	****************************************************************/

	T_UBYTE laub_str[5] = {0,0,0,0,0};
	T_UBYTE lub_i = 4, lub_j = 0;

	while(lub_val){
		laub_str[lub_i] = lub_val%10;
		lub_val = lub_val/10;
		lub_i--;
	}
	if(lsb_field_length == -1){
		while(laub_str[lub_j]==0){
			lub_j++;
		}
	}else{
		lub_j = (unsigned char)(5 - lsb_field_length);
	}

	for(lub_i=lub_j; lub_i<5; lub_i++){
		LCDData(48 + laub_str[lub_i]);
	}
	
}
/********************************************************************

Position the cursor to specific part of the screen

********************************************************************/
void LCDGotoXY(T_UBYTE lub_x, T_UBYTE lub_y){
	
 	if(lub_x >= MAX_X_VALUE){
 		return;
 	}else{
 		/* Do nothing */
 	}

	switch(lub_y){
		case 0:
			break;
		case 1:
			lub_x |= SECOND_LINE;
			break;
		case 2:
			lub_x += THIRD_LINE;
			break;
		case 3:
			lub_x += FOURTH_LINE;
			break;
		default:
			/* Do nothing */
			break;
	}
	
	lub_x |= FIRST_LINE;
	
  	LCDCmd(lub_x);
  	
}
