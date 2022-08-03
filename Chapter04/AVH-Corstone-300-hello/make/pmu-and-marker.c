/*********************************************************************/
/*        Copyright (c) 2020 Arm Limited. All rights reserved.       */
/*                                                                   */
/*                         IP Selection Sandbox                      */
/*********************************************************************/
/* PMU functionality for all systems */

#include "pmu-and-marker.h"
#include <stdio.h>

#if defined(M0p) || defined(M4) || defined(M7) || defined(M23) || defined(M33) || defined(M55)
#include "pmu_M.h"
#endif

#if defined(R5) || defined(R8) || defined(R52) || defined(A32)
#include "pmu_ARv7.h"
#endif

#if defined(A35) || defined(A53) || defined(A55)
#include "pmu_Av8.h"
#endif

unsigned int start = 0, stop = 0;

/* 
** Start tracking pmu metrics for region of interest
*/
void start_marker() 
{
//    SOFTWARE_MARK = 1;  /* Memory write to indicate software region of interest is starting */

#if defined(M7) || defined (M33) 
    start_dwt();                // Enable and start data watchdog timers
#endif

#if defined(M0p) || defined(M4) || defined (M23) || defined(M55) 
    start_systick();            // Enable and start systick timer
#endif

#if defined(R5) || defined(R8) || defined(R52) || defined(A32)
    enable_pmu_user_access();  // Allow access to PMU from User Mode

    enable_pmu();              // Enable the PMU

    pmn_config(0, 0x8);        // Configure counter 0 to count instructions retired
    pmn_config(1, 0x13);       // Configure counter 1 to count memory accesses
    pmn_config(2, 0x3);        // Configure counter 2 to count L1 dcache refill
    pmn_config(3, 0x4);        // Configure counter 3 to count L1 dcache accesses


    enable_pmn(0);             // Enable counter 0
    enable_pmn(1);             // Enable counter 1
    enable_pmn(2);             // Enable counter 2
    enable_pmn(3);             // Enable counter 3
    enable_ccnt();             // Enable CCNT

    reset_ccnt();              // Reset the CCNT (cycle counter)
    reset_pmn();               // Reset the configurable counters
#endif

#if defined(A53) || defined(A35) || defined(A55)
    enablePMU();   // Enable PMU

    pmnConfig(0, 0x8, 0);     //Configure counter 0 to count intructions retired
    pmnConfig(1, 0x1, 0);     //Configure counter 1 to count ICache Miss
    pmnConfig(2, 0x4, 0);     //Configure counter 2 to count DCache Miss
    pmnConfig(3, 0x6, 0);     //Configure counter 3 to count Memory Reads

    //Enable the Programmable Counters
    enablePMN(0);
    enablePMN(1);
    enablePMN(2);
    enablePMN(3);
    enableCCNT();

    //Reset CCNT and the Counters
    resetCCNT();
    resetPMN();
#endif
}


/* 
** Memory write to indicate the software region of interest is ending 
*/
void stop_marker() 
{

//    SOFTWARE_MARK = 0;

#if defined(M7) || defined(M33)
    stop_dwt();
    
    print_marker();
#endif

#if defined(M0p) || defined(M4) || defined(M23) || defined(M55) 
    stop_systick();

    print_marker();
#endif

#if defined(R5) || defined(R8) || defined(R52) || defined(A32)
    disable_ccnt();            // Stop CCNT 
    disable_pmn(0);            // Stop counter 0 
    disable_pmn(1);            // Stop counter 1 
    disable_pmn(2);            // Stop counter 2 
    disable_pmn(3);            // Stop counter 3 
 
    print_marker();
#endif

#if defined(A53) || defined(A35) || defined(A55)
    disableCCNT();
    disablePMN(0);
    disablePMN(1);
    disablePMN(2);
    disablePMN(3);

    print_marker();
#endif
}


/* 
** Print results of counters 
*/
void print_marker() 
{
    printf("\n______________________");
    printf("\nMarked software performance monitor results:\n\n");

#if defined(M7) || defined(M33)
    printf("CCNT = %u\n", CM_DWT_CYCCNT);
    printf("CPICNT = %u\n", CM_DWT_CPICNT);
    printf("EXCCNT  = %u\n", CM_DWT_EXCCNT);
    printf("SLEEPCNT = %u\n", CM_DWT_SLEEPCNT);
    printf("LSUCNT = %u\n", CM_DWT_LSUCNT);
    printf("FOLDCNT = %u\n", CM_DWT_FOLDCNT);
#endif

#if defined(M0p) || defined(M4) || defined(M23) || defined(M55)
    printf("CCNT = %u\n", (SysTick_START - SysTick_CVR));
    if (SysTick_CSR & 0x10000)
        printf("WARNING: counter has overflowed, more than 16,777,215 cycles");
#endif

#if defined(R5) || defined(R8) || defined(R52) || defined(A32)
    float inst,cycl,cycl_inst;

    printf("Instructions Executed = %u\n",  read_pmn(0) );
    printf("Cycle Count (CCNT) = %u\n",     read_ccnt() );
    printf("Memory accesses = %u\n",        read_pmn(1) );
    printf("L1 Data cache refills = %u\n",  read_pmn(2) );
    printf("L1 Data cache accesses = %u\n", read_pmn(3) );

    inst=read_pmn(0);
    cycl=read_ccnt();
    cycl_inst=cycl/inst;

    printf("Average cycles per instruction = %f\n",cycl_inst);
#endif

#if defined(A53) || defined(A35) || defined(A55)
    float inst,cycl,cycl_inst;

    printf("Instructions Executed = %u\n",  readPMN(0) );
    printf("Cycle Count (CCNT) = %llu\n",     readCCNT() );
    printf("I Cache Misses = %u\n",        readPMN(1) );
    printf("L1 Data cache Misses = %u\n",  readPMN(2) );
    printf("Memory Reads = %u\n", readPMN(3) );

    inst=readPMN(0);
    cycl=readCCNT();
    cycl_inst=cycl/inst;

    printf("Average cycles per instruction = %f\n",cycl_inst);
#endif

    // End of printing
    printf("\nEnd of marked software performance monitor results.\n");
    printf("______________________\n");
}

void __reset_cycle_counter()
{

}

void __start_cycle_counter()
{

#if defined(M7) || defined(M33)
    start = CM_DWT_CYCCNT;
#endif

#if defined(M0p) || defined(M4) || defined (M23) || defined(M55) 
    start = SysTick_CVR;
#endif

#if defined(R5) || defined(R8) || defined(R52) || defined(A32)
    start = read_ccnt();
#endif

#if defined(A53) || defined(A35) || defined(A55)
    start = readCCNT();
#endif
}

void __stop_cycle_counter()
{

#if defined(M7) || defined(M33)
    stop = CM_DWT_CYCCNT;
#endif

#if defined(M0p) || defined(M4) || defined (M23) || defined(M55) 
    stop = SysTick_CVR;
#endif

#if defined(R5) || defined(R8) || defined(R52) || defined(A32)
    stop = read_ccnt();
#endif

#if defined(A53) || defined(A35) || defined(A55)
    stop = readCCNT();
#endif
}


unsigned __get_cycle_count()
{

#if defined(M7) || defined(M33)
    return stop - start;
#endif

#if defined(M0p) || defined(M4) || defined (M23) || defined(M55) 
    return start - stop;
#endif

#if defined(R5) || defined(R8) || defined(R52) || defined(A32)
    return stop - start;
#endif

#if defined(A53) || defined(A35) || defined(A55)
    return stop - start;
#endif

}

