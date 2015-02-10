/* ###################################################################
**     Filename    : main.c
**     Project     : Lab5
**     Processor   : MK64FN1M0VLL12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-02-08, 12:33, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


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
#include "FAT1.h"
#include "SD1.h"
#include "SS1.h"
#include "CD1.h"
#include "TmDt1.h"
#include "UTIL1.h"
#include "SM2.h"
#include "WAIT2.h"
#include "TMOUT1.h"
#include "CS1.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "TU1.h"
#include "Temp.h"
#include "AdcLdd1.h"
#include "Photocell.h"
#include "AdcLdd2.h"
#include "Timer.h"
#include "UTIL2.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes  */
#include "Globals.h"
#include "PDC1.h"
#include "TempProbe.h"
#include "PhotoCell.h"
#include "stdio.h"
#include "math.h"
#include "LoggerApp.h"


/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Local Variable Definitions */
	char tempStr[14];
	char pcellStr[14];
	char dataStr[14];
	uint8_t cnt=0;

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Initialize Relevant Variables */
    oneSecondFlag = OFF;

    tempProbe.adcBits = 0;
    tempProbe.V = 0.0;
    tempProbe.adcflag = FALSE;
    tadcval = 0.0;

    photoCell.adcBits = 0;
    photoCell.V = 0.0;
    photoCell.adcflag = FALSE;
    padcval = 0.0;

    // Initialize file for sd card
    init_File();
    // Initialize date
    TmDt1_SetDate(2016,2,9);
    TmDt1_SetTime(7,58,30,0);

    PDC1_SplashScreen();
    WAIT1_Waitms(2000);
    PDC1_Clear();


    PDC1_WriteLineStr(1,"  Conditions  ");

    for(;;)
    {
  	  if(oneSecondFlag)
  	  {
  		  // Take Measurements
  		  (void)Temp_Measure(FALSE);
  		  (void)Photocell_Measure(FALSE);

  		  while(!(tempProbe.adcflag && photoCell.adcflag))
  		  {
  			  // Wait until all adcs are done measuring
  			  // Can do something in the mean time
  		  }
  		  // Get Values
  		  (void)Temp_GetValue16(&tempProbe.adcBits);
  		  (void)Photocell_GetValue16(&photoCell.adcBits);
  		  tempProbe_convert(&tempProbe);
  		  photoCell_convert(&photoCell);
  		  // Reset adc flags
  		  tempProbe.adcflag = FALSE;
  		  photoCell.adcflag = FALSE;
  		  // Reset second flag
  		  oneSecondFlag = OFF;
  		  LogToFile();
  		  cnt++;
  	  }


  	  if(photoCell.lux>=1000)
  	  {
  		  PDC1_Sun(32,1);
  	  }
  	  else if(300<=photoCell.lux && photoCell.lux<1000)
  	  {
  		  PDC1_Cloud(32,1);
  	  }
  	  else if(photoCell.lux <300)
  	  {
  		  PDC1_Moon(32,1);
  	  }
  	  // Create Strings
  	  snprintf(tempStr,14,"%07.2f", tempProbe.tempF);
  	  snprintf(pcellStr, 14,"%07.4f", photoCell.lux);
  	  snprintf(dataStr,14,"%05.1fF|%07.4f", tempProbe.tempF, photoCell.lux);
  	  // Display Strings
  	  PDC1_WriteLineStr(4," Temp |  LUX  ");
  	  PDC1_WriteLineStr(5,dataStr);

  	  if(cnt>=10)
  	  {
  		  Err();
  	  }
    }


  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.4 [05.11]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
