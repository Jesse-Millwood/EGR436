/*
 * Debounce.c
 *
 *  Created on: Jan 26, 2015
 *      Author: jesse
 */

#include "Debounce.h"
#include "EncBTN_INT.h"


void debouncepin_init(debouncedpin* pin)
{
	pin->timer	 			= 0;
	pin->debounce_status	= IDLE;
	pin->pinstatus			= HIGH;
	pin->onstate			= LOW;
	pin->offstate			= HIGH;
}

void debouncepin_chck(debouncedpin* pin)
{
	if(pin->debounce_status == DONE)
	{
		pin->pinstatus = EncBTN_INT_GetVal();
	}
}




