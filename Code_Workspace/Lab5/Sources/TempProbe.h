/*
 * Temp.h
 *
 *  Created on: Feb 1, 2015
 *      Author: jesse
 */

#ifndef TEMP_H_
#define TEMP_H_

#include "PE_Types.h"
#include "Globals.h"

/* Type Definitions */
typedef struct TempProbe
{
	volatile uint16_t 		adcBits; 	// Bits read from adc
	float 					V;	 		// Voltage Representation
	volatile bool			adcflag; 	// flag indicating state of adc read
	float 					tempF; 		// Temperature in F
	float 					tempC; 		// Temperature in C
}tprobe;

/* Global Variables */

tprobe tempProbe;
uint16_t tadcval;

/* Function Prototypes */
void tempProbe_convert(tprobe* TempProbe);



#endif /* TEMP_H_ */
