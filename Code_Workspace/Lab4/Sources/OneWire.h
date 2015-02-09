/*
 * OneWire.h
 *
 *  Created on: Feb 7, 2015
 *      Author: jesse
 *  Instructions:
 *  	Requires PE components
 *  		* Wait  	: OneWireWait
 *  		* BitIO 	: OneWireData
 *  		* TimerUnit	: OneWireTimer
 *  		* ExtInt	: OneWireDataInt
 */

#ifndef ONEWIRE_H_
#define ONEWIRE_H_

#include "PE_Types.h"
#include "OneWireTimer.h"
#include "OneWireData.h"
#include "OneWireDataInt.h"
#include "OneWireWait.h"
/* Macro Definitions */
#define CMD_RESET		0x00 	// dummy value, no byte is actually sent
#define CMD_SKIPROM		0xCC
#define	CMD_MATCHROM	0x55
#define CMD_READROM		0x33
#define CMD_SEARCHROM	0xF0
#define CMD_ConvertT	0x44
#define CMD_RDSCRCH		0xBE
#define CMD_WRTSCRCH	0x4E
#define CMD_CPSCRCH		0x48
#define CMD_RECALLE		0xB8
#define CMD_READPWR		0xB4
/* Type Definitions */
typedef enum OneWireState
{
	NA,
	RESET0,
	RESET1,
	TX,
	RX
}onewire_state;


typedef struct OneWireDev
{
	volatile uint8_t 		presence_us;
	volatile onewire_state 	status;
	LDD_TDeviceData* timerptr;
	volatile uint16_t count_current;
	uint16_t count_max;
	volatile uint8_t  txReadyFlag;
	uint8_t  scratchpad_indx;
	uint8_t  scratchpad[9];
	/* Scratch Pad Memory Map
	 * 0: Temperature MSB |  S  |  S  |  S  |  S  |  S  | 2^6 | 2^5 | 2^4 |
	 * 1: Temperature LSB | 2^3 | 2^2 | 2^1 | 2^0 | 2^-1| 2^-2| 2^-3| 2^-4|
	 * 2: TH - User set Alarm temperature
	 * 3: TL - User set Alarm temperature
	 * | S | 2^6 | 2^5 | 2^4 | 2^3 | 2^2 | 2^1 | 2^0 |
	 * 4: Configuration Register - User set
	 * | 0 | R1 | R0 | 1 | 1 | 1 | 1 | 1 |
	 * 5: Reserved 0xFF
	 * 6: Reserved
	 * 7: Reserved 0x10
	 * 8: CRC
	 *
	 */

}oneWireDev;

/* Function Prototypes */
void init_OneWireDev(oneWireDev* device);
void WaitPresence_OneWireDev(void);
void TX_OneWireDev(uint8_t bytetx);
void getTemp_OneWireDev(oneWireDev* device);
void ReadScratchPad_OneWireDev(oneWireDev* device);


/* Global Variable Definitions */
oneWireDev DS18B20;



#endif /* ONEWIRE_H_ */
