/*
 * DispUtil.c
 *
 *  Created on: Feb 1, 2015
 *      Author: jesse
 *
 *      Display Utilities
 */

#include "DispUtil.h"
#include "PDC1.h"
#include "stdio.h"




void Display4XNumberCentered(uint16_t dispnum, uint8_t y)
{
	char dispnumChar[4];
	snprintf(dispnumChar,4,"%0.3i",dispnum);

	WriteChar4X(dispnumChar[0], 22 ,y);
	WriteChar4X(dispnumChar[1], 31 ,y);
	WriteChar4X(dispnumChar[2], 43 ,y);
}



