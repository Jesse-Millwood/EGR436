/* ###################################################################
**     Filename    : Events.c
**     Project     : Lab4
**     Processor   : MK64FN1M0VLL12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-02-01, 18:49, # CodeGen: 0
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

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */
#include "PhotoCell.h"
#include "TempProbe.h"
#include "Globals.h"
#include "OneWire.h"

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
**     Event       :  Photocell_OnEnd (module Events)
**
**     Component   :  Photocell [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Photocell_OnEnd(void)
{
	photoCell.adcflag = TRUE;
}

/*
** ===================================================================
**     Event       :  Photocell_OnCalibrationEnd (module Events)
**
**     Component   :  Photocell [ADC]
**     Description :
**         This event is called when the calibration has been finished.
**         User should check if the calibration pass or fail by
**         Calibration status method./nThis event is enabled only if
**         the <Interrupt service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Photocell_OnCalibrationEnd(void)
{

}

/*
** ===================================================================
**     Event       :  Temp_OnEnd (module Events)
**
**     Component   :  Temp [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Temp_OnEnd(void)
{
	tempProbe.adcflag = TRUE;
}

/*
** ===================================================================
**     Event       :  Temp_OnCalibrationEnd (module Events)
**
**     Component   :  Temp [ADC]
**     Description :
**         This event is called when the calibration has been finished.
**         User should check if the calibration pass or fail by
**         Calibration status method./nThis event is enabled only if
**         the <Interrupt service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void Temp_OnCalibrationEnd(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  Timer_OnCounterRestart (module Events)
**
**     Component   :  Timer [TimerUnit_LDD]
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
void Timer_OnCounterRestart(LDD_TUserData *UserDataPtr)
{
	// Timer Restarts every 1 second
	if(!oneSecondFlag)
	{
		oneSecondFlag = ON;
	}
}

/*
** ===================================================================
**     Event       :  OneWireTimer_OnCounterRestart (module Events)
**
**     Component   :  OneWireTimer [TimerUnit_LDD]
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
void OneWireTimer_OnCounterRestart(LDD_TUserData *UserDataPtr)
{
  // Restarts every 5us
	if(DS18B20.status == RESET1)
	{
		DS18B20.count_current ++;
	}
}

/*
** ===================================================================
**     Event       :  OneWireDataInt_OnInterrupt (module Events)
**
**     Component   :  OneWireDataInt [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void OneWireDataInt_OnInterrupt(void)
{
	// On Falling edge
	if(DS18B20.status == RESET0)
	{
		// reset device counter
		DS18B20.count_current = 0;
		OneWireDataInt_SetEdge(1);	// set for rising edge
		DS18B20.status = RESET1;
	}
	else if(DS18B20.status == RESET1)
	{
		DS18B20.presence_us = DS18B20.count_current * 5;
		DS18B20.txReadyFlag = TRUE;
	}
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
