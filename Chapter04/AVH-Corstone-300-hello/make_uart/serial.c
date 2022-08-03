/*
** Copyright (c) 2018 Arm Limited. All rights reserved.
*/

#include "uart.h"
#include <stdio.h>



//  UART Code
// ================
void uart_config(uint32_t wUARTFrequency)
{
    CMSDK_UART0->CTRL = 0;         /* Disable UART when changing configuration */
    CMSDK_UART0->BAUDDIV = wUARTFrequency / 115200ul;    /* 25MHz / 38400 = 651 */
    CMSDK_UART0->CTRL = CMSDK_UART_CTRL_TXEN_Msk|CMSDK_UART_CTRL_RXEN_Msk;  
}

int stdout_putchar(char txchar)
{
    if (txchar == 10) stdout_putchar((char) 13);

    while(CMSDK_UART0->STATE & CMSDK_UART_STATE_TXBF_Msk);
    CMSDK_UART0->DATA = (uint32_t)txchar;

    return (int) txchar;
}

int stderr_putchar(char txchar)
{
    return stdout_putchar(txchar);
}

void ttywrch (int ch)
{
	stdout_putchar(ch);
}



// ReTargeting Code
// ================
#ifdef UART

asm("  .global __use_no_semihosting\n");

struct __FILE {int handle;};
FILE __stdout;
FILE __stdin;
FILE __stderr;
    
/**
   Writes the character specified by c (converted to an unsigned char) to
   the output stream pointed to by stream, at the position indicated by the
   associated file position indicator (if defined), and advances the
   indicator appropriately. If the file position indicator is not defined,
   the character is appended to the output stream.

  \param[in] c       Character
  \param[in] stream  Stream handle

  \return    The character written. If a write error occurs, the error
             indicator is set and fputc returns EOF.
*/
__attribute__((weak))
int fputc (int c, FILE * stream)
{
    if (stream == &__stdout) {
        return (stdout_putchar(c));
    }

    if (stream == &__stderr) {
        return (stderr_putchar(c));
    }

    return (-1);
}


void _sys_exit(int return_code)
{
    while(1);
}

#endif
 

