/* ###################################################################
**     Filename    : main.c
**     Project     : Lab4
**     Processor   : MK64FN1M0VLL12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-02-01, 18:49, # CodeGen: 0
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
#include "Temp.h"
#include "AdcLdd1.h"
#include "Photocell.h"
#include "AdcLdd2.h"
#include "PDC1.h"
#include "RESpin1.h"
#include "SCEpin1.h"
#include "D_Cpin1.h"
#include "WAIT1.h"
#include "SM1.h"
#include "Timer.h"
#include "OneWireData.h"
#include "BitIoLdd1.h"
#include "OneWireWait.h"
#include "OneWireDataInt.h"
#include "ExtIntLdd1.h"
#include "OneWireTimer.h"
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
#include "OneWire.h"
#include "math.h"


/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Local Variable Definitions */
  char tempStr[14];
  char pcellStr[14];
  char dataStr[14];
  uint8_t temparray[9];
  uint16_t DStemp;
  float DStempF;

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


  PDC1_SplashScreen();
  WAIT1_Waitms(2000);
  PDC1_Clear();

  init_OneWireDev(&DS18B20);


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

	  /*
	  getTemp_OneWireDev(&DS18B20);
	  for(uint8_t k=0; k<9; k++)
	  {
		  temparray[k] = DS18B20.scratchpad[k];
	  }
	  DStemp = DS18B20.scratchpad[0];
	  DStemp = DStemp<<8;
	  DStemp |= DS18B20.scratchpad[1];
	  DStemp &= 0x7F; // I know it is positive so lop off the sign bits


	  uint8_t index = 0;
	  DStempF = 0.0;
	  for(int8_t i=-4;i<11;i++)
	  {
		  DStempF += ((DStemp>>index)&0x01)*powf(2,i);
		  index ++;
	  }
	  snprintf(tempStr,14,"T:%07.2f",DStempF);
	  PDC1_WriteLineStr(3,tempStr);
	  */
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
