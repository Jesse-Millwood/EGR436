/*
 * PhotoCell.c
 *
 *  Created on: Feb 1, 2015
 *      Author: jesse
 */

#include "PhotoCell.h"
#include "math.h"


// Resistor divider parameters
#define R		10000.0		// 100k top of resistor divider

void photoCell_convert(pcell* PCell)
{
	// Convert measured adc value to a voltage
	PCell->V = (VBITS)*PCell->adcBits;
	// Convert Voltage to a Lux value
	PCell->lux = powf(((powf(10,4.903)*(VMAX-PCell->V))/(PCell->V*R)),2.0);
}


