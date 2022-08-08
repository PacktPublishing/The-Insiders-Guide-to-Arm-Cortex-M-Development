/*********************************************************************/
/*        Copyright (c) 2020 Arm Limited. All rights reserved.       */
/*                                                                   */
/*                         IP Selection Sandbox                      */
/*********************************************************************/
/* PMU variables for Cortex-M Cores */

#include <stdint.h>

void start_dwt(void);
void stop_dwt(void);
void start_systick(void);
void stop_systick(void);

/* DWT Variables */
#define CM_DWT_CYCCNTENA_BIT   (1UL<<0)
#define CM_TRCENA_BIT          (1UL<<24)

#define CM_DWT_CONTROL         (*((volatile uint32_t*)0xE0001000))
#define CM_DWT_CYCCNT          (*((volatile uint32_t*)0xE0001004))
#define CM_DWT_LAR             (*((volatile uint32_t*)0xE0001FB0))
#define CM_DEMCR               (*((volatile uint32_t*)0xE000EDFC))

#define CM_DWT_CPICNT          (*((volatile uint32_t*)0xE0001008))
#define CM_DWT_EXCCNT          (*((volatile uint32_t*)0xE000100C))
#define CM_DWT_SLEEPCNT        (*((volatile uint32_t*)0xE0001010))
#define CM_DWT_LSUCNT          (*((volatile uint32_t*)0xE0001014))
#define CM_DWT_FOLDCNT         (*((volatile uint32_t*)0xE0001018))


/* Systick variables */
#define SysTick_BASE          (0xE000E000UL +  0x0010UL) 
#define SysTick_START         0xFFFFFF

#define SysTick_CSR           (*((volatile uint32_t*)(SysTick_BASE + 0x0UL)))
#define SysTick_RVR           (*((volatile uint32_t*)(SysTick_BASE + 0x4UL)))
#define SysTick_CVR           (*((volatile uint32_t*)(SysTick_BASE + 0x8UL)))

#define SysTick_Enable        0x1
#define SysTick_ClockSource   0x4
