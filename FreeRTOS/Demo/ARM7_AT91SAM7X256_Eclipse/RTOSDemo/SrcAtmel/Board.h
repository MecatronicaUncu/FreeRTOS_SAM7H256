/*----------------------------------------------------------------------------
*         ATMEL Microcontroller Software Support  -  ROUSSET  -
*----------------------------------------------------------------------------
* The software is delivered "AS IS" without warranty or condition of any
* kind, either express, implied or statutory. This includes without
* limitation any warranty or condition with respect to merchantability or
* fitness for any particular purpose, or against the infringements of
* intellectual property rights of others.
*----------------------------------------------------------------------------
* File Name           : Board.h
* Object              : Olimex AT91SAM7-P256 Evaluation Board Features Definition File.
*
* Creation            : JPP   16/Jun/2004
*----------------------------------------------------------------------------
*/
#ifndef Board_h
#define Board_h

#include "AT91SAM7X256.h"
#define __inline inline

#define true	-1
#define false   0

//-----------------  
// Leds Definition   
//-----------------  
//                                 PIO		PA    PB   PIN   
#define LED1            (1<<8) // PA8		RD    PCK2  10   
#define NB_LEB		1

#define LED_MASK        (LED1)


//--------------  
// Master Clock   
//--------------  

#define EXT_OC          18432000   // Exetrnal ocilator MAINCK
#define MCK             47923200   // MCK (PLLRC div by 2)
#define MCKKHz          (MCK/1000) //

#endif // Board_h   
