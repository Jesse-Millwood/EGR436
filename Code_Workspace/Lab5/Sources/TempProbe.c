/*
 * Temp.c
 *
 *  Created on: Feb 1, 2015
 *      Author: jesse
 */

#include "TempProbe.h"


void tempProbe_convert(tprobe* TempProbe)
{
	// Convert adc to voltage
	TempProbe->V = (TempProbe->adcBits*(VBITS));
	// Convert voltage to F
	TempProbe->tempF = (TempProbe->V*1000)/(10);
	// Convert voltage to C
	TempProbe->tempC = (TempProbe->tempF - 32)/1.8;
}
