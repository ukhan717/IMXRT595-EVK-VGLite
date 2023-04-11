/*******************************************************************************
*
* E M B E D D E D   W I Z A R D   P R O J E C T
*
*                                                Copyright (c) TARA Systems GmbH
*                                    written by Paul Banach and Manfred Schweyer
*
********************************************************************************
*
* This software is delivered "as is" and shows the usage of other software
* components. It is provided as an example software which is intended to be
* modified and extended according to particular requirements.
*
* TARA Systems hereby disclaims all warranties and conditions with regard to the
* software, including all implied warranties and conditions of merchantability
* and non-infringement of any third party IPR or other rights which may result
* from the use or the inability to use the software.
*
********************************************************************************
*
* DESCRIPTION:
*   This file is part of the interface (glue layer) between an Embedded Wizard
*   generated UI application and the board support package (BSP) of a dedicated
*   target.
*   This template is responsible to initialize the system clock of the hardware,
*   to provide a timer tick for the Embedded Wizard UI application and to get
*   access to the realtime clock (RTC). Additionally, this file contains some
*   performance measurements to analyse the CPU usage of the UI application.
*
*******************************************************************************/

#include "fsl_rtc.h"
#include "ewconfig.h"
#include "ew_bsp_clock.h"
#include "ew_bsp_os.h"


#if EW_CPU_LOAD_MEASURING == 1

  /* variables for cycle counter / CPU load measurement */
  static unsigned long          WorkingTime  = 0;
  static unsigned long          SleepingTime = 0;
  static unsigned long          PrevCycCnt   = 0;

#endif

/* helper function to initialize measuring unit (cycle counter) */
static void CycleCounterInit( void )
{
  /* Enable TRC */
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

  /* Unlock DWT registers */
  if ((*(uint32_t*)0xE0001FB4) & 1)
    *(uint32_t*)0xE0001FB0 = 0xC5ACCE55;

  /* clear the cycle counter */
  DWT->CYCCNT = 0;

  /* start the cycle counter */
  DWT->CTRL = 0x40000001;

  /* initialize counters */
  #if EW_CPU_LOAD_MEASURING == 1

    WorkingTime   = 0;
    SleepingTime  = 0;
    PrevCycCnt    = 0;

  #endif
}


#if EW_CPU_LOAD_MEASURING == 1

/* helper function to get cycle counter value since last call */
static unsigned long GetCycleCounterDelta( void )
{
  unsigned long cycCnt;
  unsigned long result;

  /* get delta between current counter value and last counter value */
  cycCnt = DWT->CYCCNT;
  result = cycCnt - PrevCycCnt;
  PrevCycCnt = cycCnt;

  return result;
}

#endif


#if EW_USE_OPERATING_SYSTEM == 0
/*******************************************************************************
* FUNCTION:
*   SysTick_Handler
*
* DESCRIPTION:
*   System tick handler. Called on every system tick.
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void SysTick_Handler(void)
{
  EwBspOsSystickHandler();
}
#endif


/*******************************************************************************
* FUNCTION:
*   EwBspClockInit
*
* DESCRIPTION:
*   Initialises the system clock and the real time clock.
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwBspClockInit( void )
{
  /* set systick reload value to generate 1ms interrupt */
  SysTick_Config( CLOCK_GetFreq(kCLOCK_CoreSysClk) / 1000U );

  /* initialize system cycle counter (also used for display synchronisation) */
  CycleCounterInit();

  /* Init RTC */
  RTC_Init(RTC);
}


/*******************************************************************************
* FUNCTION:
*   EwBspClockGetTime
*
* DESCRIPTION:
*   Returns the current time in seconds since 01.01.1970.
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   The current time in seconds since 01.01.1970.
*
*******************************************************************************/
unsigned long EwBspClockGetTime( void )
{
  return RTC->COUNT;
}


/*******************************************************************************
* FUNCTION:
*   EwBspClockSetTime
*
* DESCRIPTION:
*   Sets the given time in seconds since 01.01.1970 at real time clock (RTC).
*
* ARGUMENTS:
*   aTime - the time in seconds since 01.01.1970 to set in real time clock.
*
* RETURN VALUE:
*   None.
*
*******************************************************************************/
void EwBspClockSetTime( unsigned long aTime )
{
  /* RTC time counter has to be stopped before setting the date & time in the TSR register */
  RTC_StopTimer(RTC);

  RTC->COUNT = aTime;

  /* Start the RTC time counter */
  RTC_StartTimer(RTC);
}


/*******************************************************************************
* FUNCTION:
*   EwBspClockGetCpuLoad
*
* DESCRIPTION:
*   Returns the current CPU load as percent value.
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   The current CPU load.
*
*******************************************************************************/
 int EwBspClockGetCpuLoad( void )
{
  int cpuLoad = 0;

  #if EW_CPU_LOAD_MEASURING == 1

    /* get actual counter value */
    WorkingTime += GetCycleCounterDelta();

    /* calculate CPU load as percent value */
    cpuLoad = ( int ) ( WorkingTime / (( SleepingTime + WorkingTime ) / 100 ));

    /* clear accumulated counter values */
    WorkingTime  = 0;
    SleepingTime = 0;

  #endif

  return cpuLoad;
}


/*******************************************************************************
* FUNCTION:
*   EwBspClockCpuLoadSetActive
*
* DESCRIPTION:
*   Starts the CPU load counting. Call this function whenever CPU processing
*   is needed.
*
* ARGUMENTS:
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwBspClockCpuLoadSetActive( void )
{
  #if EW_CPU_LOAD_MEASURING == 1

    SleepingTime += GetCycleCounterDelta();

  #endif
}


/*******************************************************************************
* FUNCTION:
*   EwBspClockCpuLoadSetIdle
*
* DESCRIPTION:
*   Stops the CPU load counting. Call this function whenever CPU processing is
*   currently not needed since the program execution is waiting for some system
*   event.
*
* ARGUMENTS:
*   None
*
* RETURN VALUE:
*   None
*
*******************************************************************************/
void EwBspClockCpuLoadSetIdle( void )
{
  #if EW_CPU_LOAD_MEASURING == 1

    WorkingTime += GetCycleCounterDelta();

  #endif
}


/* mli, msy */
