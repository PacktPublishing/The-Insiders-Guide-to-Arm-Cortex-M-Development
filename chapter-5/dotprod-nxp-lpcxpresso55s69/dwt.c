#include <stdio.h> 
#include "dwt.h" 

void start_dwt() 
{ 
    DWT_LAR = 0xC5ACCE55; 
    DEMCR |= TRCENA_BIT; 
    DWT_CYCCNT = 0; 
    DWT_CONTROL |= DWT_CYCCNTENA_BIT; 
} 

void stop_dwt() 
{ 
    DWT_CONTROL &= ~DWT_CYCCNTENA_BIT; 

    printf("CCNT = %u\n", DWT_CYCCNT); 
    printf("CPICNT = %u\n", DWT_CPICNT); 
    printf("EXCCNT  = %u\n", DWT_EXCCNT); 
    printf("SLEEPCNT = %u\n", DWT_SLEEPCNT); 
    printf("LSUCNT = %u\n", DWT_LSUCNT); 
    printf("FOLDCNT = %u\n", DWT_FOLDCNT); 
} 
