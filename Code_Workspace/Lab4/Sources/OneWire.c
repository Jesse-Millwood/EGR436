/*
 * OneWire.c
 *
 *  Created on: Feb 7, 2015
 *      Author: jesse
 */

#include "OneWire.h"


init_OneWireDev(oneWireDev* device)
{
	device->presence_us = 0;
	device->status = NA;
	device->timerptr = OneWireTimer_Init(NULL);
	OneWireTimer_Disable(device->timerptr);
	OneWireDataInt_Disable();
	device->count_current = 0;
	device->count_max = 24; 	// 120us/5us
	device->scratchpad_indx = 0;
	device->txReadyFlag = FALSE;
}

WaitPresence_OneWireDev(void)
{
	OneWireData_SetInput();
	OneWireDataInt_Enable();
	OneWireDataInt_SetEdge(0);
	OneWireTimer_Enable(DS18B20.timerptr);
	DS18B20.count_current = 0;
	DS18B20.txReadyFlag = FALSE;
	while(DS18B20.txReadyFlag == FALSE)//|| (DS18B20.count_current <= DS18B20.count_max))
	{	}
	OneWireDataInt_Disable();
	DS18B20.status = TX;


}
TX_OneWireDev(uint8_t bytetx)
{
	// local variables
	uint8_t i=0;
	// Ensure that data pin is an output
	OneWireData_SetOutput();
	switch(bytetx)
	{
		case CMD_RESET:
			DS18B20.status = RESET0;
			OneWireData_ClrVal();
			OneWireWait_Waitus(500);
			break;
		case CMD_SKIPROM:
		case CMD_ConvertT:
		case CMD_RDSCRCH:
			// Writing Bit by bit
			for(i=0;i<8;i++)
			{
				OneWireData_ClrVal();
				// Shift the bits one by one
				if(((bytetx>>i)&0x01) == 1)
				{
					OneWireData_SetVal();
				}
				OneWireWait_Waitus(5);
				OneWireData_SetVal();
			}
			OneWireData_SetVal();
			break;
		default:
			break;
	}
}
void ReadScratchPad_OneWireDev(oneWireDev* device)
{
	uint8_t byte=0;
	uint8_t bit=0;
	uint8_t numreadbytes = 9;
	for(byte=0;byte<numreadbytes;byte++)
	{
		for(bit=0;bit<8;bit++)
		{
			OneWireData_SetOutput();
			OneWireData_ClrVal();
			OneWireWait_Waitus(1);
			OneWireData_SetInput();
			OneWireWait_Waitus(15);
			device->scratchpad[byte] |= ((0x01<<bit)&OneWireData_GetVal());
			OneWireWait_Waitus(6);
		}
	}

}
getTemp_OneWireDev(oneWireDev* device)
{
	TX_OneWireDev(CMD_RESET);
	WaitPresence_OneWireDev();
	TX_OneWireDev(CMD_SKIPROM);
	TX_OneWireDev(CMD_ConvertT);
	TX_OneWireDev(CMD_RESET);
	WaitPresence_OneWireDev();
	TX_OneWireDev(CMD_SKIPROM);
	TX_OneWireDev(CMD_RDSCRCH);
	ReadScratchPad_OneWireDev(device);

}


