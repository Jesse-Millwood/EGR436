/* ###################################################################
**     Filename    : Events.h
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
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
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

#ifdef __cplusplus
extern "C" {
#endif 


// Globals
volatile uint8_t interrupt_flag;
volatile uint16_t timer_ms;


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
void Cpu_OnNMI(void);


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
void SM1_OnBlockSent(LDD_TUserData *UserDataPtr);

void EncA_INT_OnInterrupt(void);
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
void DebounceTimer_OnCounterRestart(LDD_TUserData *UserDataPtr);

void EncBTN_INT_OnInterrupt(void);
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

void EncB_INT_OnInterrupt(void);
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

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __Events_H*/
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
