/* ###################################################################
**     Filename    : main.c
**     Project     : Lab3_RotaryEncoder2
**     Processor   : MK64FN1M0VLL12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-01-26, 18:45, # CodeGen: 0
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
#include "EncB_INT.h"
#include "ExtIntLdd2.h"
#include "EncBTN_INT.h"
#include "ExtIntLdd3.h"
#include "LED_G.h"
#include "BitIoLdd4.h"
#include "LED_R.h"
#include "BitIoLdd5.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "stdio.h"
#include "Encoder.h"
#include "Debounce.h"
#include "Globals.h"
#include "DispUtil.h"


/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */
  char valAstr[10];
  char valBstr[10];
  char intfstr[10];
  char cntstr[10];
  char grcode[10];
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Initialize Hardware Inputs */
  encoder_init(&rotaryEncoder);
  rotaryEncoder.btn.pinstatus 	= Enc_BTN_GetVal();

  // Display splash screen
  benderSplash();
  GeneralWait_Waitms(3000);
  PDC1_Clear();

  /*
   * For Testing
  PDC1_WriteLineStr(1, "Rotary Test");
  for(;;)
  {
	  // Check status of button
	  debouncepin_chck(&rotaryEncoder.btn);
	  // Build Strings
	  snprintf(valAstr,10,"A: %i",EncA_GetVal());
	  snprintf(valBstr,10,"B: %i",EncB_GetVal());
	  // Display Strings to Screen
	  PDC1_WriteLineStr(2, valAstr);
	  PDC1_WriteLineStr(3, valBstr);
	  // Show Gray Code
	  snprintf(grcode, 10, "Gray: 0x%X", rotaryEncoder.gray);
	  PDC1_WriteLineStr(4,grcode);
	  // Show Count value
	  snprintf(cntstr,10,"Count:%0.3i  ",rotaryEncoder.count);
	  PDC1_WriteLineStr(5,cntstr);

	  if(rotaryEncoder.btn.pinstatus == rotaryEncoder.btn.onstate)
	  {
		  LED_G_ClrVal();
		  LED_R_ClrVal();
	  }


  }
  */

  /* Displaying Large Count */
  PDC1_WriteLineStr(1, " Rotary Count");
  for(;;)
  {
	  Display4XNumberCentered(rotaryEncoder.count, 3);
	  if(rotaryEncoder.btn.pinstatus == rotaryEncoder.btn.onstate)
	  {
		  LED_G_ClrVal();
		  LED_R_ClrVal();
	  }
	  else if(rotaryEncoder.btn.pinstatus == rotaryEncoder.btn.offstate)
	  {
		  LED_G_SetVal();
		  LED_R_SetVal();
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
