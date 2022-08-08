/*********************************************************************/
/*        Copyright (c) 2020 Arm Limited. All rights reserved.       */
/*                                                                   */
/*                         IP Selection Sandbox                      */
/*********************************************************************/
/* PMU functions for Cortex-M Cores */

#include "pmu_M.h"
#include <stdio.h>



/* DWT settings, for Cortex-M cores that use DWT */
void start_dwt()
{
    CM_DEMCR |= CM_TRCENA_BIT;
    CM_DWT_LAR = 0xC5ACCE55;
    CM_DWT_CYCCNT = 0;
    CM_DWT_CONTROL |= CM_DWT_CYCCNTENA_BIT; 
}
void stop_dwt()
{
    CM_DWT_CONTROL &= ~CM_DWT_CYCCNTENA_BIT;
}



/* systick settings, for Cortex-M cores that use systick */
void start_systick()
{
    SysTick_RVR = SysTick_START;
    SysTick_CVR = 0;
    SysTick_CSR |=  (SysTick_Enable | SysTick_ClockSource);
}
void stop_systick()
{
    SysTick_CSR &= ~SysTick_Enable;
}
