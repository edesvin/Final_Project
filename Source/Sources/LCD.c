/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: LCD.c $
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
 * $Log: LCD.c  $
  ============================================================================*/

/* Includes */
/*============================================================================*/
#include "LCD.h"

/* Constants and types  */
/*============================================================================*/
#define DATA_0 						0x00
#define DATA_1 						0x01
#define DATA_2 						0x02
#define DATA_3 						0x03

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
#define DATA_OFFSET					48
#define TENTH						10
#define MAX_FIELD_LENGTH			5
#define STM_1us						64
#define STM_500ns					32
#define STM_30ms					0x1D4C00
#define MIN_VALID_INDEX				0
#define MAX_VALID_INDEX				7

/* Private functions prototypes */
/*============================================================================*/
void delay_1u(void);
void delay_500n(void);
void delay_30ms(void);

/* Private functions */
/*==============================================================================
* Function: delay_1u
* 
* Description: 
*
==============================================================================*/
void delay_1u(void){
	Clear_STM();					/* Reset STM counter */	
	while( STM_Value <= STM_1us ){
		/* Wait for 1 us */
	}
}

/*==============================================================================
* Function: delay_500n 
* 
* Description: 
*
==============================================================================*/
void delay_500n(void){
	Clear_STM();					/* Reset STM counter */	
	while( STM_Value <= STM_500ns ){
		/* Wait for 500 ns */
	}
}

/*==============================================================================
* Function: delay_30ms
* 
* Description: 
*
==============================================================================*/
void delay_30ms(void){
	Clear_STM();					/* Reset STM counter */	
	while( STM_Value <= STM_30ms ){
		/* Wait for 30 ms */
	}
}

/*==============================================================================
* Function: LCDByte
* 
* Description: 
*
==============================================================================*/
void LCDByte(T_UBYTE lub_byte, T_UBYTE lub_isdata)
{
    //Sends a byte to the LCD in 4bit mode
    //cmd=0 for data
    //cmd=1 for command

    T_UBYTE lub_high_byte, lub_low_byte;		
    T_UBYTE lub_temp, lub_lcd_data;

    lub_high_byte = lub_byte >> 4; 		/* Divide the byte that will be sent in 4 byte mode */	
    lub_low_byte = lub_byte & 0x0F;

    if(lub_isdata == 0){				/* Check whether it is a command */	
		Set_LCD_RS(RESET);
    }else{
		Set_LCD_RS(SET);
	}
	
    delay_500n();		

    Set_LCD_E(SET);

    lub_lcd_data = Read_LCD_Data();
    lub_temp = ( lub_lcd_data & (~(MASK_LOW_HALF_BYTE))) | lub_high_byte;
    Set_LCD_Data( DATA_0 , ((lub_temp & FIRST_BIT)  >> DATA_0) & FIRST_BIT );
    Set_LCD_Data( DATA_1 , ((lub_temp & SECOND_BIT) >> DATA_1) & FIRST_BIT );
    Set_LCD_Data( DATA_2 , ((lub_temp & THIRD_BIT)  >> DATA_2) & FIRST_BIT );
    Set_LCD_Data( DATA_3 , ((lub_temp & FOURTH_BIT) >> DATA_3) & FIRST_BIT );
	
    delay_1u();			
    
    Set_LCD_E(RESET); 	/* Now that the data lines are stable, E is pulled low for transmission */

    delay_1u();

    Set_LCD_E(SET); 	/* Send the lower nibble */

    lub_lcd_data = Read_LCD_Data();
    lub_temp = ( lub_lcd_data & (~(MASK_LOW_HALF_BYTE))) | lub_low_byte;
    Set_LCD_Data( DATA_0 , ((lub_temp & FIRST_BIT)  >> DATA_0) & FIRST_BIT );
    Set_LCD_Data( DATA_1 , ((lub_temp & SECOND_BIT) >> DATA_1) & FIRST_BIT );
    Set_LCD_Data( DATA_2 , ((lub_temp & THIRD_BIT)  >> DATA_2) & FIRST_BIT );
    Set_LCD_Data( DATA_3 , ((lub_temp & FOURTH_BIT) >> DATA_3) & FIRST_BIT );

    delay_1u();			

    Set_LCD_E(RESET); /* The transmission of the lower nibble is done */

    delay_1u();		

    LCDBusyLoop(); /* Check whether the LCD is Busy */
    
}

/*==============================================================================
* Function: LCDBusyLoop
* 
* Description: 
*
==============================================================================*/
void LCDBusyLoop(){
	
    T_UBYTE lub_temp, lub_busy, lub_status;

	Set_LCD_Data_Input();    /* Set Data lines as INPUT */
	
    /* Change LCD mode */
	Set_LCD_RW(SET);		/* Read mode */
    Set_LCD_RS(RESET);		/* Read status */

    /*Let the RW/RS lines stabilize */
    delay_500n();	
    
	do{
		Set_LCD_E(SET);

		delay_500n();	 /* Wait for data to become available */

		lub_status = Read_LCD_Data();
		lub_status = lub_status << 4;

		delay_500n();	

		Set_LCD_E(RESET);
		delay_1u();

		Set_LCD_E(SET);
		delay_500n();	

		lub_temp = Read_LCD_Data();
		lub_temp &= MASK_LOW_HALF_BYTE;

		lub_status = lub_status | lub_temp;

		lub_busy = lub_status & MASK_0X80;

		delay_500n();	

		Set_LCD_E(RESET);
		delay_1u();
			
    }while(lub_busy);

	Set_LCD_RW(RESET);      /* Write mode */
    Set_LCD_Data_Output();  /* Set Data lines as OUTPUTS */	
}

/*==============================================================================
* Function: LCDInit
* 
* Description: This function initializes the LCD module. This must be called
* before calling LCD related functions.
*
==============================================================================*/
void LCDInit(T_UBYTE lub_style){

	T_UBYTE lub_i;

	T_UBYTE lub_custom_char[]=
	{
		0x0C, 0x12, 0x12, 0x0C, 0x00, 0x00, 0x00, 0x00, /* Char0 - Degree symbol */
		0x01, 0x07, 0x1F, 0x1F, 0x1F, 0x1F, 0x19, 0x00, /* Char1 - Seat belt 1   */
		0x1F, 0x00, 0x0E, 0x0E, 0x0E, 0x00, 0x1F, 0x00, /* Char2 - Seat belt 2 	 */
		0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, /* Char3 - Seat belt 3   */
		0x03, 0x02, 0x0E, 0x0A, 0x0E, 0x02, 0x03, 0x00, /* Char4 - Seat belt 4   */
		0x10, 0x1C, 0x1F, 0x1F, 0x1F, 0x1F, 0x13, 0x00, /* Char5 - Seat belt 5   */
		0x03, 0x06, 0x0E, 0x0F, 0x1E, 0x1C, 0x19, 0x1A, /* Char6 				 */
		0x18, 0x0C, 0x0E, 0x1E, 0x0F, 0x17, 0x03, 0x03, /* Char7				 */
	};
        
	

	delay_30ms(); 							/* After power on, wait for LCD to initialize	*/
	Set_LCD_E(SET);							/* Set ENABLE signal pin						*/
	Set_LCD_Data(DATA_1, FOUR_BIT_MODE);  	/* Set 4-bit mode 								*/ 
	delay_1u();								/* Delay one microsecond						*/
	Set_LCD_E(RESET);						/* Reset ENABLE signal pin						*/
	delay_1u();								/* Delay one microsecond						*/
	
	LCDBusyLoop();							/* Wait for LCD									*/ 

	/* Now the LCD is in 4-bit mode */

	LCDCmd(FOUR_BIT_TWO_LINE_FORMAT);		/* Function set 4-bit, 2 line 5x7 dot format  	*/
    LCDCmd(DISPLAY_ON | lub_style);	  		/* Display On									*/

    LCDCmd(SET_CUSTOM_CHARS);				/* Set Custom Char								*/


	for(lub_i=0; lub_i<sizeof(lub_custom_char); lub_i++){
		LCDData(lub_custom_char[lub_i]);	/* Set each of the custom chars					*/
	}

}

/*==============================================================================
* Function: LCDWriteString
* 
* Description: Function that receives a string to print it in the LCD.
*
==============================================================================*/
void LCDWriteString(const char *cpub_msg){
	
	T_UBYTE lub_cc_support;
	
	while(*cpub_msg != '\0'){
		if(*cpub_msg == '%'){ 							 /* Custom Char Support								    */
			cpub_msg++;				/* Pointer position is incremented to point at the index of the custom char */
			lub_cc_support = (T_UBYTE)(*cpub_msg - '0'); /* Get the numeric value of the char variable          */
			
			/* Make sure it is a valid index */
			if( lub_cc_support >= MIN_VALID_INDEX && lub_cc_support <= MAX_VALID_INDEX ){ 	
				LCDData(lub_cc_support);			 	 /* Print the selected custom char	  					 */
			}else{
				LCDData('%');							 /* Print the percentage sign if it is not a valid index */
				LCDData(*cpub_msg);						 /* Print the invalid index								 */
			}
		}else{										  
			LCDData(*cpub_msg); 						 /* Print the received char								 */
		}
		cpub_msg++;							/* Pointer position is incremented to point at the next char value   */
	}
}
/*==============================================================================
* Function: LCDWriteInt
* 
* Description: Function that receives a number and a field length to print it
* in the LCD.
*
==============================================================================*/
void LCDWriteInt(T_UBYTE lub_val, T_SBYTE lsb_field_length){
	
	T_UBYTE laub_str[MAX_FIELD_LENGTH] = {0,0,0,0,0};	/* Array to save the bytes of the 						 */
	T_UBYTE lub_i = 4, lub_j = 0;

	while(lub_val){
		laub_str[lub_i] = lub_val % TENTH;
		lub_val = lub_val / TENTH;
		lub_i--;
	}
	if(lsb_field_length == -1){
		while(laub_str[lub_j]==0){
			lub_j++;
		}
	}else{
		lub_j = (unsigned char)(MAX_FIELD_LENGTH - lsb_field_length);
	}

	for(lub_i = lub_j; lub_i < MAX_FIELD_LENGTH; lub_i++){
		LCDData(DATA_OFFSET + laub_str[lub_i]);
	}
	
}
/*==============================================================================
* Function: LCDGotoXY
* 
* Description: Set the position of the cursor to an specific part of the screen.
*
==============================================================================*/
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
