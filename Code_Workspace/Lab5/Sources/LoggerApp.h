/*
 * LoggerApp.h
 *
 *  Created on: Feb 8, 2015
 *      Author: jesse
 */

#ifndef LOGGERAPP_H_
#define LOGGERAPP_H_
/* Libraries to include */
#include "WAIT2.h"
#include "FAT1.h"
#include "TempProbe.h"
#include "PhotoCell.h"



/* Macro Definitions */
#define WRITE_BUFFER_LENGTH 	48


/* Global Variables */
static FAT1_FATFS fileSystemObject;
static FIL fp;

/* Function Prototypes */
void Err(void);
void init_File(void);
void LogToFile(void);



#endif /* LOGGERAPP_H_ */
