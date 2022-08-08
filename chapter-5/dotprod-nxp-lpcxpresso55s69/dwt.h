#include <stdint.h> 

void start_dwt(void); 
void stop_dwt(void); 

/* DWT Variables */ 
#define DWT_CYCCNTENA_BIT (1UL << 0) 
#define TRCENA_BIT (1UL << 24) 

#define DWT_CONTROL (*((volatile uint32_t*) 0xE0001000)) 
#define DWT_CYCCNT (*((volatile uint32_t*) 0xE0001004)) 
#define DWT_LAR (*((volatile uint32_t*) 0xE0001FB0)) 
#define DEMCR (*((volatile uint32_t*) 0xE000EDFC)) 

#define DWT_CPICNT (*((volatile uint32_t* )0xE0001008)) 
#define DWT_EXCCNT (*((volatile uint32_t*) 0xE000100C)) 
#define DWT_SLEEPCNT (*((volatile uint32_t*) 0xE0001010)) 
#define DWT_LSUCNT (*((volatile uint32_t*) 0xE0001014)) 
#define DWT_FOLDCNT (*((volatile uint32_t*) 0xE0001018)) 
