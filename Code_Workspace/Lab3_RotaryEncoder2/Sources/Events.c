/* ###################################################################
**     Filename    : Events.c
**     Project     : Lab3_RotaryEncoder2
**     Processor   : MK64FN1M0VLL12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-01-26, 18:45, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMI - void Cpu_OnNMI(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"
#include "Init_Config.h"
#include "PDD_Includes.h"

// User Included
#include "Encoder.h"
#include "Globals.h"


#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Event       :  Cpu_OnNMI (module Events)
**
**     Component   :  Cpu [MK64FN1M0LL12]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMI(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  SM1_OnBlockSent (module Events)
**
**     Component   :  SM1 [SPIMaster_LDD]
*/
/*!
**     @brief
**         This event is called after the last character from the
**         output buffer is moved to the transmitter. This event is
**         available only if the SendBlock method is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer is passed
**                           as the parameter of Init method. 
*/
/* ===================================================================*/
void SM1_OnBlockSent(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  EncA_INT_OnInterrupt (module Events)
**
**     Component   :  EncA_INT [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void EncA_INT_OnInterrupt(void)
{
	// Called on rising and falling edges of the Encoder A pin
	uint8_t Aval;
	uint8_t Bval;
	// Read the inputs
	Aval = EncA_INT_GetVal();
	Bval = EncB_INT_GetVal();
	// Build Grey Code
	encoder_buildGrayCode(&rotaryEncoder, Aval, Bval);
	// Set count and direction of encoder
	encoder_DirCnt(&rotaryEncoder);

}

/*
** ===================================================================
**     Event       :  DebounceTimer_OnCounterRestart (module Events)
**
**     Component   :  DebounceTimer [TimerUnit_LDD]
*/
/*!
**     @brief
**         Called if counter overflow/underflow or counter is
**         reinitialized by modulo or compare register matching.
**         OnCounterRestart event and Timer unit must be enabled. See
**         [SetEventMask] and [GetEventMask] methods. This event is
**         available only if a [Interrupt] is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer passed as
**                           the parameter of Init method.
*/
/* ===================================================================*/
void DebounceTimer_OnCounterRestart(LDD_TUserData *UserDataPtr)
{
	// Timer restarts every 50us
	if(rotaryEncoder.btn.debounce_status == DEBOUNCING)
	{
		if(rotaryEncoder.btn.timer >= DEB_50US_CNT)
		{
			if(EncBTN_INT_GetVal() == rotaryEncoder.btn.onstate)
			{
				rotaryEncoder.btn.debounce_status = DONE;
				rotaryEncoder.btn.pinstatus = rotaryEncoder.btn.onstate;
			}
			else
			{
				rotaryEncoder.btn.debounce_status = IDLE;
				rotaryEncoder.btn.pinstatus = rotaryEncoder.btn.offstate;
			}
			// reset the timer counter
			rotaryEncoder.btn.timer = 0;
		}
		else
		{
			rotaryEncoder.btn.timer ++;
		}
	}
}

/*
** ===================================================================
**     Event       :  EncBTN_INT_OnInterrupt (module Events)
**
**     Component   :  EncBTN_INT [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void EncBTN_INT_OnInterrupt(void)
{
	/*
	 * Button is pulled up internally
	 */
	// Called on falling edge of the Btn pin
	if(rotaryEncoder.btn.debounce_status == IDLE)
	{
		// change the debounce status of the button
		rotaryEncoder.btn.debounce_status = DEBOUNCING;
		rotaryEncoder.btn.timer = 0;
	}
}
/*
** ===================================================================
**     Event       :  EncB_INT_OnInterrupt (module Events)
**
**     Component   :  EncB_INT [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void EncB_INT_OnInterrupt(void)
{
	// Called on rising and falling edges of the Encoder B pin
	uint8_t Aval;
	uint8_t Bval;
	// Read the inputs
	Aval = EncA_INT_GetVal();
	Bval = EncB_INT_GetVal();
	// Build Grey Code
	encoder_buildGrayCode(&rotaryEncoder, Aval, Bval);
	// Set count and direction of encoder
	encoder_DirCnt(&rotaryEncoder);
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

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
