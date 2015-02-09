/*
 * Encoder.h
 *
 *  Created on: Jan 26, 2015
 *      Author: jesse
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include "Debounce.h"
/* Macros */
#define ORIGINALCNT 	32768

/* Type Definitions */
typedef enum Direction{
	NA,
	CLOCKWISE,
	COUNTERCLOCKWISE
}direction;
typedef struct Encoder
{
	int16_t 		count;
	uint8_t 		prev;
	uint8_t 		curr;
	uint8_t 		gray;
	debouncedpin 	btn;
	direction 		dir;
}encoder;

/* Global Variables */

/* Functions */
void encoder_init(volatile encoder* enc);
void encoder_buildGrayCode(volatile encoder* enc, uint8_t A, uint8_t B);
void encoder_DirCnt(volatile encoder* enc);

#endif /* ENCODER_H_ */
