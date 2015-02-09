/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : TmDt1.c
**     Project     : Lab5
**     Processor   : MK64FN1M0VLL12
**     Component   : GenericTimeDate
**     Version     : Component 01.020, Driver 01.00, CPU db: 3.00.000
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-02-08, 13:55, # CodeGen: 3
**     Abstract    :
**         Software date/time module.
**     Settings    :
**          Component name                                 : TmDt1
**          Tick Time (ms)                                 : 10
**          RTOS                                           : Disabled
**          Initialization                                 : Enabled
**            Init in startup                              : yes
**            Date                                         : 2012-07-22
**            Time                                         : 05:51:31 pm
**     Contents    :
**         AddTick  - void TmDt1_AddTick(void);
**         AddTicks - void TmDt1_AddTicks(uint16_t nofTicks);
**         SetTime  - uint8_t TmDt1_SetTime(uint8_t Hour, uint8_t Min, uint8_t Sec, uint8_t Sec100);
**         GetTime  - uint8_t TmDt1_GetTime(TIMEREC *Time);
**         SetDate  - uint8_t TmDt1_SetDate(uint16_t Year, uint8_t Month, uint8_t Day);
**         GetDate  - uint8_t TmDt1_GetDate(DATEREC *Date);
**         Init     - void TmDt1_Init(void);
**         DeInit   - void TmDt1_DeInit(void);
**
**     (c) Copyright Freescale Semiconductor, 2014
**     http: www.freescale.com
**     Source code is based on the original TimeDate Processor Expert component.
** ###################################################################*/
/*!
** @file TmDt1.c
** @version 01.00
** @brief
**         Software date/time module.
*/         
/*!
**  @addtogroup TmDt1_module TmDt1 module documentation
**  @{
*/         

/* MODULE TmDt1. */

#include "TmDt1.h"

#define TmDt1_TICK_TIME_MS \
  10                                    /* Period in milliseconds as defined in component properties, at which TmDt1._AddTick() is called */
#if TmDt1_TICK_TIME_MS==0
  #error "Tick period cannot be zero!"
#endif
#define TmDt1_TICKS_PER_S  (1000/TmDt1_TICK_TIME_MS) /* number of timer ticks per second */

static uint8_t CntDay;                 /* Day counter */
static uint8_t CntMonth;               /* Month counter */
static uint16_t CntYear;               /* Year Counter */
static uint32_t tickCntr;              /* Software tick counter (1 tick = TmDt1_TICK_TIME_MS ms) */

/* Table of month length (in days) */
static const  uint8_t ULY[12] = {31U,28U,31U,30U,31U,30U,31U,31U,30U,31U,30U,31U}; /* Un-leap-year */
static const  uint8_t  LY[12] = {31U,29U,31U,30U,31U,30U,31U,31U,30U,31U,30U,31U}; /* Leap-year */

/*
** ===================================================================
**     Method      :  TmDt1_SetTime (component GenericTimeDate)
**     Description :
**         This method sets a new actual time.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Hour            - Hours (0 - 23)
**         Min             - Minutes (0 - 59)
**         Sec             - Seconds (0 - 59)
**         Sec100          - Hundredth of seconds (0 - 99)
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
#ifdef __HIWARE__
  #pragma MESSAGE DISABLE C5905 /* multiplication with one (happens if TmDt1_TICKS_PER_S is 100) */
#endif
uint8_t TmDt1_SetTime(uint8_t Hour, uint8_t Min, uint8_t Sec, uint8_t Sec100)
{
  CS1_CriticalVariable()

  if ((Sec100>99U) || (Sec>59U) || (Min>59U) || (Hour>23U)) { /* Test correctnes of given time */
    return ERR_RANGE;                  /* If not correct then error */
  }
  CS1_EnterCritical();
  tickCntr = (3600UL*TmDt1_TICKS_PER_S*(uint32_t)Hour)
              + (60UL*TmDt1_TICKS_PER_S*(uint32_t)Min)
              + (TmDt1_TICKS_PER_S*(uint32_t)Sec)
              + ((TmDt1_TICKS_PER_S/100)*(uint32_t)Sec100); /* Load given time re-calculated to TmDt1_TICK_TIME_MS ms ticks into software tick counter */
  CS1_ExitCritical();
  return ERR_OK;                       /* OK */
}
#ifdef __HIWARE__
  #pragma MESSAGE DEFAULT C5905 /* multiplication with one  */
#endif

/*
** ===================================================================
**     Method      :  TmDt1_AddTick (component GenericTimeDate)
**     Description :
**         Needs to be called periodically by the application to
**         increase the time tick count.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TmDt1_AddTick(void)
{
  const uint8_t* ptr;                  /* Pointer to ULY/LY table */
  CS1_CriticalVariable()

  CS1_EnterCritical();                 /* need exclusive access to tick counter */
  tickCntr++;                          /* Software timer counter increment by timer period */
  CS1_ExitCritical();                  /* end of critical section */
  if (tickCntr >= 24*3600UL*TmDt1_TICKS_PER_S) { /* Does the counter reach 24 hours? */
    tickCntr -= 24*3600UL*TmDt1_TICKS_PER_S; /* If yes then reset it by subtracting exactly 24 hours */
    CS1_EnterCritical();
    CntDay++;                          /* Increment day counter */
    CS1_ExitCritical();
    if (CntYear & 0x03U) {             /* Is this year un-leap-one? */
      ptr = ULY;                       /* Set pointer to un-leap-year day table */
    } else {                           /* Is this year leap-one? */
      ptr = LY;                        /* Set pointer to leap-year day table */
    }
    ptr--;                             /* Decrement the pointer */
    if (CntDay > ptr[CntMonth]) {      /* Day counter overflow? */
      CntDay = 1U;                     /* Set day counter on 1 */
      CS1_EnterCritical();
      CntMonth++;                      /* Increment month counter */
      CS1_ExitCritical();
      if (CntMonth > 12U) {            /* Month counter overflow? */
        CntMonth = 1U;                 /* Set month counter on 1 */
        CS1_EnterCritical();
        CntYear++;                     /* Increment year counter */
        CS1_ExitCritical();
      }
    }
  }
}

/*
** ===================================================================
**     Method      :  TmDt1_AddTicks (component GenericTimeDate)
**     Description :
**         Same as AddTick(), but multiple ticks can be added in one
**         step.
**     Parameters  :
**         NAME            - DESCRIPTION
**         nofTicks        - Number of ticks to be added
**     Returns     : Nothing
** ===================================================================
*/
void TmDt1_AddTicks(uint16_t nofTicks)
{
  while(nofTicks>0) {
    TmDt1_AddTick();
    nofTicks--;
  }
}

/*
** ===================================================================
**     Method      :  TmDt1_GetTime (component GenericTimeDate)
**     Description :
**         This method returns current time.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Time            - Pointer to the structure TIMEREC. It
**                           contains actual number of hours, minutes,
**                           seconds and hundredth of seconds.
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t TmDt1_GetTime(TIMEREC *Time)
{
  uint32_t ticks;                      /* temporary variable of software tick counter */
  CS1_CriticalVariable()

  CS1_EnterCritical();                 /* need exclusive access to tick counter */
  ticks = tickCntr;                    /* actual number of ticks */
  CS1_ExitCritical();                  /* end of critical section */
  Time->Hour = (uint8_t)(ticks/(3600*TmDt1_TICKS_PER_S)); /* number of hours */
  ticks %= (3600*TmDt1_TICKS_PER_S);   /* remainder of ticks inside hour */
  Time->Min = (uint8_t)(ticks/(60*TmDt1_TICKS_PER_S)); /* number of minutes */
  ticks %= (60*TmDt1_TICKS_PER_S);     /* remainder of ticks inside minute */
  Time->Sec = (uint8_t)(ticks/TmDt1_TICKS_PER_S); /* number of seconds */
  ticks %= TmDt1_TICKS_PER_S;
  Time->Sec100 = (uint8_t)((ticks*(1000/TmDt1_TICKS_PER_S))/10); /* number of 1/100 seconds */
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  TmDt1_SetDate (component GenericTimeDate)
**     Description :
**         This method sets a new actual date.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Year            - Years (16-bit unsigned integer)
**         Month           - Months (8-bit unsigned integer)
**         Day             - Days (8-bit unsigned integer)
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t TmDt1_SetDate(uint16_t Year, uint8_t Month, uint8_t Day)
{
  const uint8_t* ptr;                  /* Pointer to ULY/LY table */
  CS1_CriticalVariable()

  if ((Year < 1998U) || (Year > 2099U) || (Month > 12U) || (Month == 0U) || (Day > 31U) || (Day == 0U)) { /* Test correctness of given parameters */
    return ERR_RANGE;                  /* If not correct then error */
  }
  ptr = (((Year & 0x03U) != 0U) ? ULY : LY); /* Set pointer to leap-year or un-leap-year day table */
  if (ptr[Month - 1U] < Day) {         /* Does the obtained number of days exceed number of days in the appropriate month & year? */
    return ERR_RANGE;                  /* If yes (incorrect date inserted) then error */
  }
  CS1_EnterCritical();                 /* Save the PS register */
  CntDay = Day;                        /* Set day counter to the given value */
  CntMonth = Month;                    /* Set month counter to the given value */
  CntYear = Year;                      /* Set year counter to the given value */
  CS1_ExitCritical();                  /* Restore the PS register */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  TmDt1_GetDate (component GenericTimeDate)
**     Description :
**         This method returns current date.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * Date            - Pointer to DATEREC
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t TmDt1_GetDate(DATEREC *Date)
{
  CS1_CriticalVariable()

  CS1_EnterCritical();                 /* Save the PS register */
  Date->Year = CntYear;                /* Year */
  Date->Month = CntMonth;              /* Month */
  Date->Day = CntDay;                  /* Day */
  CS1_ExitCritical();                  /* Restore the PS register */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  TmDt1_Init (component GenericTimeDate)
**     Description :
**         Initialization method
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TmDt1_Init(void)
{
  /* initialize date/time as set in properties */
  (void)TmDt1_SetTime(17, 51, 31, 0);
  (void)TmDt1_SetDate(2012, 7, 22);
}

/*
** ===================================================================
**     Method      :  TmDt1_DeInit (component GenericTimeDate)
**     Description :
**         Deinitializes the driver.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TmDt1_DeInit(void)
{
  /* Nothing to do */
}

/* END TmDt1. */

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
