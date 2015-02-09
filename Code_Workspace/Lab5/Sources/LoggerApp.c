/*
 * LoggerApp.c
 *
 *  Created on: Feb 8, 2015
 *      Author: jesse
 */


#include "LoggerApp.h"
#include "stdio.h"
#include "PE_Types.h"

void Err(void)
{
	for(;;)
	{

	}
}

void init_File(void)
{
	if (FAT1_Init()!=ERR_OK)
	{
		/* initialize FAT driver */
	    Err();
	}

	if (FAT1_mount(&fileSystemObject, "0", 1) !=FR_OK)
	{
		/* mount file system */
		Err();
	}
}

void LogToFile(void)
{
	/* Local Variables */
	char write_buf[WRITE_BUFFER_LENGTH];
	uint8_t buflen;
	UINT bw;
	TIMEREC time;

	/* Open File */
	if(FAT1_open(&fp, "./log.txt", FA_OPEN_ALWAYS|FA_WRITE) != FR_OK)
	{
		Err();
	}
	/* Move to the end of the file */
	if(FAT1_lseek(&fp, fp.fsize) != FR_OK || fp.fptr != fp.fsize)
	{
		Err();
	}
	/* get time */
	if(TmDt1_GetTime(&time)!=ERR_OK)
	{
		Err();
	}
	/* write data */
	buflen = snprintf(write_buf,WRITE_BUFFER_LENGTH,"\0%i:%i:%i,%%05.1f,%07.4f\n",
					time.Hour,time.Min,time.Sec,tempProbe.tempF,photoCell.lux);

	if (FAT1_write(&fp, write_buf, buflen, &bw)!=FR_OK)
	{
	    (void)FAT1_close(&fp);
	    Err();
	}
	  /* closing file */
	  (void)FAT1_close(&fp);

}

