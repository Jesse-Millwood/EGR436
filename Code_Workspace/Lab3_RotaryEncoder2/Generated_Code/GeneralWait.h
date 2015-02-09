/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : GeneralWait.h
**     Project     : Lab3_RotaryEncoder2
**     Processor   : MK64FN1M0VLL12
**     Component   : Wait
**     Version     : Component 01.067, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-01-26, 19:37, # CodeGen: 6
**     Abstract    :
**          Implements busy waiting routines.
**     Settings    :
**          Component name                                 : GeneralWait
**          Manual Clock Values                            : Disabled
**          Delay100usFunction                             : Delay100US
**          RTOS                                           : Disabled
**          Watchdog                                       : Disabled
**     Contents    :
**         Wait10Cycles   - void GeneralWait_Wait10Cycles(void);
**         Wait100Cycles  - void GeneralWait_Wait100Cycles(void);
**         WaitCycles     - void GeneralWait_WaitCycles(uint16_t cycles);
**         WaitLongCycles - void GeneralWait_WaitLongCycles(uint32_t cycles);
**         Waitms         - void GeneralWait_Waitms(uint16_t ms);
**         Waitus         - void GeneralWait_Waitus(uint16_t us);
**         Waitns         - void GeneralWait_Waitns(uint16_t ns);
**         WaitOSms       - void GeneralWait_WaitOSms(void);
**
**     License   : Open Source (LGPL)
**     Copyright : Erich Styger, 2013-2014, all rights reserved.
**     Web       : www.mcuoneclipse.com
**     This an open source software implementing waiting routines using Processor Expert.
**     This is a free software and is opened for education,  research  and commercial developments under license policy of following terms:
**     * This is a free software and there is NO WARRANTY.
**     * No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
**     * Redistributions of source code must retain the above copyright notice.
** ###################################################################*/
/*!
** @file GeneralWait.h
** @version 01.00
** @brief
**          Implements busy waiting routines.
*/         
/*!
**  @addtogroup GeneralWait_module GeneralWait module documentation
**  @{
*/         

#ifndef __GeneralWait_H
#define __GeneralWait_H

/* MODULE GeneralWait. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited beans */

#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif


#define GeneralWait_NofCyclesMs(ms, hz)  ((ms)*((hz)/1000)) /* calculates the needed cycles based on bus clock frequency */
#define GeneralWait_NofCyclesUs(us, hz)  ((us)*(((hz)/1000)/1000)) /* calculates the needed cycles based on bus clock frequency */
#define GeneralWait_NofCyclesNs(ns, hz)  (((ns)*(((hz)/1000)/1000))/1000) /* calculates the needed cycles based on bus clock frequency */


#define GeneralWait_WAIT_C(cycles) \
     ( (cycles)<=10 ? \
          GeneralWait_Wait10Cycles() \
        : GeneralWait_WaitCycles((uint16_t)cycles) \
      )                                      /*!< wait for some cycles */


void GeneralWait_Wait10Cycles(void);
/*
** ===================================================================
**     Method      :  GeneralWait_Wait10Cycles (component Wait)
**     Description :
**         Wait for 10 CPU cycles.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void GeneralWait_Wait100Cycles(void);
/*
** ===================================================================
**     Method      :  GeneralWait_Wait100Cycles (component Wait)
**     Description :
**         Wait for 100 CPU cycles.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void GeneralWait_WaitCycles(uint16_t cycles);
/*
** ===================================================================
**     Method      :  GeneralWait_WaitCycles (component Wait)
**     Description :
**         Wait for a specified number of CPU cycles (16bit data type).
**     Parameters  :
**         NAME            - DESCRIPTION
**         cycles          - The number of cycles to wait.
**     Returns     : Nothing
** ===================================================================
*/

void GeneralWait_Waitms(uint16_t ms);
/*
** ===================================================================
**     Method      :  GeneralWait_Waitms (component Wait)
**     Description :
**         Wait for a specified time in milliseconds.
**     Parameters  :
**         NAME            - DESCRIPTION
**         ms              - How many milliseconds the function has to
**                           wait
**     Returns     : Nothing
** ===================================================================
*/

/* we are having a static clock configuration: implement as macro/inlined version */
#define GeneralWait_Waitus(us)  \
       (  ((GeneralWait_NofCyclesUs((us),CPU_BUS_CLK_HZ)==0)||(us)==0) ? \
          (void)0 : \
          ( ((us)/1000)==0 ? (void)0 : GeneralWait_Waitms((uint16_t)((us)/1000))) \
          , (GeneralWait_NofCyclesUs(((us)%1000), CPU_BUS_CLK_HZ)==0) ? (void)0 : \
            GeneralWait_WAIT_C(GeneralWait_NofCyclesUs(((us)%1000), CPU_BUS_CLK_HZ)) \
       )
/*
** ===================================================================
**     Method      :  GeneralWait_Waitus (component Wait)
**     Description :
**         Wait for a specified time in microseconds.
**     Parameters  :
**         NAME            - DESCRIPTION
**         us              - How many microseconds the function has to
**                           wait
**     Returns     : Nothing
** ===================================================================
*/

/* we are having a static clock configuration: implement as macro/inlined version */
#define GeneralWait_Waitns(ns)  \
       (  ((GeneralWait_NofCyclesNs((ns), CPU_BUS_CLK_HZ)==0)||(ns)==0) ? \
          (void)0 : \
          GeneralWait_Waitus((ns)/1000) \
          , (GeneralWait_NofCyclesNs((ns)%1000, CPU_BUS_CLK_HZ)==0) ? \
              (void)0 : \
              GeneralWait_WAIT_C(GeneralWait_NofCyclesNs(((ns)%1000), CPU_BUS_CLK_HZ)) \
       )
/*
** ===================================================================
**     Method      :  GeneralWait_Waitns (component Wait)
**     Description :
**         Wait for a specified time in nano seconds.
**     Parameters  :
**         NAME            - DESCRIPTION
**         ns              - How many ns the function has to wait
**     Returns     : Nothing
** ===================================================================
*/

#define GeneralWait_WaitOSms(ms) \
  GeneralWait_Waitms(ms) /* no RTOS used, so use normal wait */
/*
** ===================================================================
**     Method      :  GeneralWait_WaitOSms (component Wait)
**     Description :
**         If an RTOS is enabled, this routine will use a non-blocking
**         wait method. Otherwise it will do a busy/blocking wait.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

#ifdef __cplusplus
}  /* extern "C" */
#endif

void GeneralWait_WaitLongCycles(uint32_t cycles);
/*
** ===================================================================
**     Method      :  GeneralWait_WaitLongCycles (component Wait)
**     Description :
**         Wait for a specified number of CPU cycles (32bit data type).
**     Parameters  :
**         NAME            - DESCRIPTION
**         cycles          - The number of cycles to wait.
**     Returns     : Nothing
** ===================================================================
*/

/* END GeneralWait. */

#endif
/* ifndef __GeneralWait_H */
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
