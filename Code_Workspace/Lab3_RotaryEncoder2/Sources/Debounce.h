/*
 * Debounce.h
 *
 *  Created on: Jan 26, 2015
 *      Author: jesse
 */

#ifndef DEBOUNCE_H_
#define DEBOUNCE_H_

/* Included Headers */
#include "PE_Types.h"

/* Macros */
#define HIGH  			1
#define ON				1
#define LOW 			0
#define OFF				0
// Counter overflows every 50us
// the user can choose the number of ms
// for convenience.
// 50us is used so that if there is multiple
// things that need be be debounced the most any
// debounced button can be off is 25us
#define DEB_MS  		5
#define DEB_50US_CNT 	DEB_MS * 20

/* Type Definitions */
typedef enum DebounceStatus
{
	IDLE,
	DEBOUNCING,
	DONE
}debstat;
typedef struct DebouncedPin
{
	uint8_t 	offstate;
	uint8_t		onstate;
	uint16_t 	timer;
	debstat 	debounce_status;
	uint8_t 	pinstatus;
}debouncedpin;

/* Functions */
void debouncepin_init(debouncedpin* pin);
void debouncepin_chck(debouncedpin* pin);



#endif /* DEBOUNCE_H_ */
