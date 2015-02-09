/*
 * PhotoCell.h
 *
 *  Created on: Feb 1, 2015
 *      Author: jesse
 */

#ifndef PHOTOCELL_H_
#define PHOTOCELL_H_

#include "PE_Types.h"
#include "Globals.h"

/* Type Definitions */
typedef struct PhotoCell
{
	volatile uint16_t		adcBits;
	float 					V;
	volatile bool 			adcflag;
	float 					lux;
}pcell;

/* Global Variables */

pcell photoCell;
uint16_t padcval;

/* Function Prototypes */
void photoCell_convert(pcell* PCell);


#endif /* PHOTOCELL_H_ */
