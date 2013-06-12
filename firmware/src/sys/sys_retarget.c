/**
 * \name sys_retarget.c 
 *
 * \author Reed
 * \date Jun 12, 2013
 *
 * \brief
 *
 * \desc
 *
 */

#include "sys.h"


#if defined( __GNUC__ )
/* Include stdio.h to pull in __REDLIB_INTERFACE_VERSION__ */
#include <stdio.h>

#if (__REDLIB_INTERFACE_VERSION__ >= 20000)
/* We are using new Redlib_v2 semihosting interface */
        #define WRITEFUNC __sys_write
        #define READFUNC __sys_readc
#else
/* We are using original Redlib semihosting interface */
        #define WRITEFUNC _write
        #define READFUNC _readc
#endif

#if defined(DEBUG_ENABLE)
#if defined(DEBUG_SEMIHOSTING)
/* Do nothing, semihosting is enabled by default in LPCXpresso */
#endif /* defined(DEBUG_SEMIHOSTING) */
#endif /* defined(DEBUG_ENABLE) */

#if !defined(DEBUG_SEMIHOSTING)
int WRITEFUNC(int iFileHandle, char *pcBuffer, int iLength)
{
#if defined(DEBUG_ENABLE)
        unsigned int i;
        for (i = 0; i < iLength; i++) {
            sys_putch(pcBuffer[i]);
        }
#endif

        return iLength;
}

/* Called by bottom level of scanf routine within RedLib C library to read
   a character. With the default semihosting stub, this would read the character
   from the debugger console window (which acts as stdin). But this version reads
   the character from the LPC1768/RDB1768 UART. */
int READFUNC(void)
{
#if defined(DEBUG_ENABLE)
        char c = sys_getch();
        return (int) c;

#else
        return (int) -1;
#endif
}

#endif /* !defined(DEBUG_SEMIHOSTING) */
#endif /* defined ( __GNUC__ ) */
