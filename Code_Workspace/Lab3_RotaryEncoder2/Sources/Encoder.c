/*
 * Encoder.c
 *
 *  Created on: Jan 26, 2015
 *      Author: jesse
 */
/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Pins1.h"
#include "PDC1.h"
#include "RESpin1.h"
#include "SCEpin1.h"
#include "D_Cpin1.h"
#include "WAIT1.h"
#include "SM1.h"
#include "EncA.h"
#include "BitIoLdd1.h"
#include "EncB.h"
#include "BitIoLdd2.h"
#include "EncA_INT.h"
#include "ExtIntLdd1.h"
#include "GeneralWait.h"
#include "DebounceTimer.h"
#include "Enc_BTN.h"
#include "BitIoLdd3.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
// User Libs
#include "Encoder.h"

void encoder_init(volatile encoder* enc)
{
	enc->count = 10;
	enc->dir = NA;
	enc->curr = 0b11;
	enc->gray = 0b1111;
	debouncepin_init(&enc->btn);

}

void encoder_buildGrayCode(volatile encoder* enc, uint8_t A, uint8_t B)
{
	enc->curr = ((A<<1) | (B)) & (0x03);
	enc->gray = ((enc->gray << 2) | (enc->curr)) & (0x0F);
}

void encoder_DirCnt(volatile encoder* enc)
{
	switch(enc->gray)
	{
		case 0b1101:
			enc->dir = COUNTERCLOCKWISE;
			break;
		case 0b0100:
			enc->dir = COUNTERCLOCKWISE;
			break;
		case 0b0010:
			enc->dir = COUNTERCLOCKWISE;
			break;
		case 0b1011:
			enc->dir = COUNTERCLOCKWISE;
			if(enc->count <= 99)
				enc->count ++;
			else
				enc->count = 100;
			LED_G_SetVal();
			LED_R_ClrVal();
			break;
		case 0b1110:
			enc->dir = CLOCKWISE;
			break;
		case 0b1000:
			enc->dir = CLOCKWISE;
			break;
		case 0b0001:
			enc->dir = CLOCKWISE;
			break;
		case 0b0111:
			enc->dir = CLOCKWISE;
			if(enc->count >= 1)
				enc->count --;
			else
				enc->count = 0;
			LED_G_ClrVal();
			LED_R_SetVal();
			break;
		default:
			break;
	}

}


