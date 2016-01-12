/*============================================================================*/
/*                        I BS SOFTWARE GROUP                                 */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*/
/*!
 * $Source: LCD.c $
 * $Revision: 1.4 $
 * &Project: Cluster_EA $
 * $Author: 	Edgar Escayola Vinagre	$
 * 				Adrian Zacarias Siete 	$
 *				
 * $Date: 11-01-2016 $
 */
/*============================================================================*/
/* DESCRIPTION :                                                              */
/** \file
*		This module configures and handles the LCD HITACHI HD44780 20x4.
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
/*                     |      Cluster_EA    |           1.4                   */
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
#define FOUR_SLOTS					0x04
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
#define MAX_X_VALUE					0x14
#define DATA_OFFSET					0x30
#define TENTH						0x0A
#define MAX_FIELD_LENGTH			0x05
#define STM_1us						0x40
#define STM_500ns					0x20
#define STM_30ms					0x1D4C00
#define MIN_VALID_INDEX				0x00
#define MAX_VALID_INDEX				0x07

/* Private functions prototypes */
/*============================================================================*/
void delay_1us(void);
void delay_500ns(void);
void delay_30ms(void);
void LCDBusyLoop(void);
/* Private functions */
/*==============================================================================
* Function: delay_1us
* 
* Description: Function that makes a delay of one microsecond.
*
==============================================================================*/
void delay_1us(void){
	Clear_STM();					/* Reset STM counter			*/	
	while( STM_VALUE <= STM_1us ){  /* Wait for the STM counter 	*/
		/* Wait for 1 us */
	}
}

/*==============================================================================
* Function: delay_500ns 
* 
* Description: Function that makes a delay of 500 nanoseconds.
*
==============================================================================*/
void delay_500ns(void){
	Clear_STM();					 /* Reset STM counter			*/	
	while( STM_VALUE <= STM_500ns ){ /* Wait for the STM counter 	*/
		/* Wait for 500 ns */
	}
}

/*==============================================================================
* Function: delay_30ms
* 
* Description: Function that makes a delay of 30 miliseconds.
*
==============================================================================*/
void delay_30ms(void){
	Clear_STM();					/* Reset STM counter 			*/	
	while( STM_VALUE <= STM_30ms ){	/* Wait for the STM counter 	*/
		/* Wait for 30 ms */
	}
}

/*==============================================================================
* Function: LCDByte
* 
* Description: Function to send a byte to the LCD in 4bit mode.
*
==============================================================================*/
void LCDByte(T_UBYTE lub_byte, T_UBYTE lub_isdata){

    T_UBYTE lub_high_byte, lub_low_byte;		
    T_UBYTE lub_temp, lub_lcd_data;

    lub_high_byte = lub_byte >> FOUR_SLOTS; /* Divide the byte that will be sent in 4 byte mode */	
    lub_low_byte = lub_byte & MASK_LOW_HALF_BYTE; /* Mask the low half of the data				*/

    if(lub_isdata == 0){				/* Check whether it is a command 						*/	
		Set_LCD_RS(RESET);				/* Reset LCD Register Select pin						*/
    }else{
		Set_LCD_RS(SET);				/* Set LCD Register Select pin							*/
	}
	
    delay_500ns();						/* Delay of 500 nanoseconds.							*/
    Set_LCD_E(SET);						/* Set LCD Enable pin									*/

    lub_lcd_data = Read_LCD_Data();												/* Read the state of the LCD Data pins	*/
    lub_temp = ( lub_lcd_data & (~(MASK_LOW_HALF_BYTE))) | (lub_high_byte);	    /* Mask the state of the LCD Data pins  */
    Set_LCD_Data( DATA_0 , ((lub_temp & FIRST_BIT)  >> DATA_0) & FIRST_BIT );   /* Set LCD Data pin 0					*/
    Set_LCD_Data( DATA_1 , ((lub_temp & SECOND_BIT) >> DATA_1) & FIRST_BIT );	/* Set LCD Data pin 0					*/
    Set_LCD_Data( DATA_2 , ((lub_temp & THIRD_BIT)  >> DATA_2) & FIRST_BIT );	/* Set LCD Data pin 0					*/
    Set_LCD_Data( DATA_3 , ((lub_temp & FOURTH_BIT) >> DATA_3) & FIRST_BIT );	/* Set LCD Data pin 0					*/
	
    delay_1us();		/* Delay of one microsecond.											 */
    Set_LCD_E(RESET); 	/* Now that the data lines are stable, E is pulled low for transmission. */
    delay_1us();		/* Delay of one microsecond.											 */
    Set_LCD_E(SET); 	/* Send the lower nibble.												 */

    lub_lcd_data = Read_LCD_Data();												/* Read the state of the LCD Data pins	*/
    lub_temp = ( lub_lcd_data & (~(MASK_LOW_HALF_BYTE))) | (lub_low_byte);	    /* Mask the state of the LCD Data pins  */
    Set_LCD_Data( DATA_0 , ((lub_temp & FIRST_BIT)  >> DATA_0) & FIRST_BIT );   /* Set LCD Data pin 0					*/
    Set_LCD_Data( DATA_1 , ((lub_temp & SECOND_BIT) >> DATA_1) & FIRST_BIT );	/* Set LCD Data pin 0					*/
    Set_LCD_Data( DATA_2 , ((lub_temp & THIRD_BIT)  >> DATA_2) & FIRST_BIT );	/* Set LCD Data pin 0					*/
    Set_LCD_Data( DATA_3 , ((lub_temp & FOURTH_BIT) >> DATA_3) & FIRST_BIT );	/* Set LCD Data pin 0					*/

    delay_1us(); 	  /* Delay of one microsecond.						 */
    Set_LCD_E(RESET); /* The transmission of the lower nibble is done. 	 */
    delay_1us();	  /* Delay of one microsecond.						 */

    LCDBusyLoop();    /* Check whether the LCD is Busy. 				 */
    
}

/*==============================================================================
* Function: LCDBusyLoop
* 
* Description: Function that checks whether the LCD is in busy state.
*
==============================================================================*/
void LCDBusyLoop(){
	
    T_UBYTE lub_temp, lub_busy, lub_status;
	
	Set_LCD_Data_Input();   /* Set Data lines as INPUT 							      */
	
    /* Change LCD mode */
	Set_LCD_RW(SET);		/* Read mode  											  */
    Set_LCD_RS(RESET);		/* Read status 											  */

    /*Let the RW/RS lines stabilize */
    delay_500ns();			/* Delay of 500 nanoseconds. 			    			  */
     
	do{
		Set_LCD_E(SET);	 	/* Set LCD Enable pin									  */

		delay_500ns();	 	/* Wait 500 nanoseconds for data to become available 	  */

		lub_status = Read_LCD_Data();	/* Read LCD data pins					      */
		lub_status = lub_status << 4;   /* Move four bits the LCD data 			      */

		delay_500ns();		/* Delay of 500 nanoseconds.							  */

		Set_LCD_E(RESET);	/* Reset LCD Enable pin								      */
		delay_1us();		/* Delay of one microsecond.							  */
		Set_LCD_E(SET);		/* Set LCD Enable pin								      */
		delay_500ns();		/* Delay of 500 nanoseconds.						      */

		lub_temp = Read_LCD_Data();		/* Read the state of the LCD Data pins		  */
		lub_temp &= MASK_LOW_HALF_BYTE; /* Mask data's low half 					  */

		lub_status = lub_status | lub_temp; /* Compare status and the data's low half */
		lub_busy = lub_status & MASK_0X80;	/* Mask status variable					  */

		delay_500ns();		/* Delay of 500 nanoseconds.							  */
		Set_LCD_E(RESET);	/* Reset LCD Enable pin								      */
		delay_1us();		/* Delay of one microsecond.							  */
			
    }while(lub_busy);		/* Repeat the cycle while the LCD is still busy			  */

	Set_LCD_RW(RESET);      /* Write mode */
    Set_LCD_Data_Output();  /* Set Data lines as OUTPUTS */	
}

/*==============================================================================
* Function: LCDInit
* 
* Description: Function that initializes the LCD module. This must be called
* before calling LCD related functions.
*
==============================================================================*/
void LCDInit(T_UBYTE lub_style){

	T_UBYTE lub_i;

	T_UBYTE lub_custom_char[]=
	{
		0x0C, 0x12, 0x12, 0x0C, 0x00, 0x00, 0x00, 0x00, /* Char0 - Degree symbol 			*/
		0x01, 0x07, 0x1F, 0x1F, 0x1F, 0x1F, 0x19, 0x00, /* Char1 - Seat belt 1   			*/
		0x1F, 0x00, 0x0E, 0x0E, 0x0E, 0x00, 0x1F, 0x00, /* Char2 - Seat belt 2 	 			*/
		0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, /* Char3 - Seat belt 3  			*/
		0x03, 0x02, 0x0E, 0x0A, 0x0E, 0x02, 0x03, 0x00, /* Char4 - Seat belt 4   			*/
		0x10, 0x1C, 0x1F, 0x1F, 0x1F, 0x1F, 0x13, 0x00, /* Char5 - Seat belt 5   			*/
		0x03, 0x06, 0x0E, 0x0F, 0x1E, 0x1C, 0x19, 0x1A, /* Char6 				 			*/
		0x18, 0x0C, 0x0E, 0x1E, 0x0F, 0x17, 0x03, 0x03, /* Char7				 			*/
	};
        
	

	delay_30ms(); 							/* After power on, wait for LCD to initialize	*/
	Set_LCD_E(SET);							/* Set ENABLE signal pin						*/
	Set_LCD_Data(DATA_1, FOUR_BIT_MODE);  	/* Set 4-bit mode 								*/ 
	delay_1us();							/* Delay one microsecond						*/
	Set_LCD_E(RESET);						/* Reset ENABLE signal pin						*/
	delay_1us();							/* Delay one microsecond						*/
	
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
		if(*cpub_msg == '%'){ 							 /* Custom Char Support								     */
			cpub_msg++;				/* Pointer position is incremented to point at the index of the custom char  */
			lub_cc_support = (T_UBYTE)(*cpub_msg - '0'); /* Get the numeric value of the char variable           */
			
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
	
	T_UBYTE laub_str[MAX_FIELD_LENGTH] = {0,0,0,0,0};	/* Array to save the bytes of the received variable	  */
	T_UBYTE lub_i = 4, lub_j = 0;

	while(lub_val){
		laub_str[lub_i] = lub_val % TENTH;	/* Get the residue of the division by ten. 	 				      */
		lub_val = lub_val / TENTH;			/* Divide the value by 10.									      */
		lub_i--;							/* Subtract one to the counter to divide the whole number.	      */
	}
	if(lsb_field_length == -1){				/* If the field length is minus one, the length is calculated.    */
		while(laub_str[lub_j] == 0){		/* While there are digits in the array, it counts.			   	  */
			lub_j++;						/* Add one to the counter.									  	  */
		}
	}else{
		lub_j = (unsigned char)(MAX_FIELD_LENGTH - lsb_field_length); /* Set the field length to the variable */
	}

	for(lub_i = lub_j; lub_i < MAX_FIELD_LENGTH; lub_i++){
		LCDData(DATA_OFFSET + laub_str[lub_i]);						  /* Print each of the digits.			  */ 
	}
	
}
/*==============================================================================
* Function: LCDGotoXY
* 
* Description: Set the position of the cursor to an specific part of the screen.
*
==============================================================================*/
void LCDGotoXY ( T_UBYTE lub_x, T_UBYTE lub_y ){
	
 	if(lub_x >= MAX_X_VALUE){		/* Make sure the x value is in range.					*/
 		return;						
 	}else{
 		/* Do nothing */
 	}

	switch(lub_y){				
		case 0:
			break;					/* The x value for the first line of y does not change. */
		case 1:
			lub_x |= SECOND_LINE;	/* Mask the x value for the second line of y. 			*/
			break;
		case 2:
			lub_x += THIRD_LINE;	/* Mask the x value for the third line of y. 			*/
			break;
		case 3:
			lub_x += FOURTH_LINE; 	/* Mask the x value for the fourth line of y.			*/
			break;
		default:
			/* Do nothing */
			break;
	}
	
	lub_x |= FIRST_LINE;			/* Mask for the any of the lines.						*/
	
  	LCDCmd(lub_x);					/* Set the position of the cursor.						*/
  	
}
