/*
 * sys_init.c
 *
 *  Created on: Jun 12, 2013
 *      Author: Reed
 */


#include "common.h"


/*!< System Clock Frequency (Core Clock)*/
uint32_t SystemCoreClock;



void sys_debug_init(void);
STATIC void SystemSetupClocking(void);



void sys_init()
{
	/* Updates SystemCoreClock global var with current clock speed */
	/* CPU core speed */
	SystemCoreClock = Chip_Clock_GetSystemClockRate();

	sys_debug_init();
}




/**************************************************************************************************
 * \brief Called by startup assembly
 */
void SystemInit(void)
{
#if defined(CORE_M3) || defined(CORE_M4)
	unsigned int *pSCB_VTOR = (unsigned int *) 0xE000ED08;

#if defined(__IAR_SYSTEMS_ICC__)
	extern void *__vector_table;

	*pSCB_VTOR = (unsigned int) &__vector_table;
#elif defined(__CODE_RED)
	extern void *g_pfnVectors;

	*pSCB_VTOR = (unsigned int) &g_pfnVectors;
#elif defined(__ARMCC_VERSION)
	extern void *__Vectors;

	*pSCB_VTOR = (unsigned int) &__Vectors;
#endif

#if defined(__FPU_PRESENT) && __FPU_PRESENT == 1
	fpuInit();
#endif

	/* Setup system clocking and memory. This is done early to allow the
          application and tools to clear memory and use scatter loading to
          external memory. */
	SystemSetupClocking();
	//SystemSetupMuxing();
	//SystemSetupMemory();
#endif
}



/* Setup system clocking */
STATIC void SystemSetupClocking(void)
{
	/* CPU clock source starts with IRC */
	Chip_Clock_SetMainPllSource(SYSCTL_PLLCLKSRC_IRC);
	Chip_Clock_SetCPUClockSource(SYSCTL_CCLKSRC_SYSCLK);

	/* Enable PBOOST for CPU clock over 100MHz */
	Chip_SYSCTL_EnableBoost();

	/* Enable main oscillator used for PLLs */
	LPC_SYSCTL->SCS = SYSCTL_OSCEC;
	while ((LPC_SYSCTL->SCS & SYSCTL_OSCSTAT) == 0) {}

	/* PLL0 clock source is 12MHz oscillator, PLL1 can only be the
           main oscillator */
	Chip_Clock_SetMainPllSource(SYSCTL_PLLCLKSRC_MAINOSC);

	/* Setup PLL0 for a 120MHz clock
           Input clock rate (FIN) is main oscillator = 12MHz
           PLL output = 120MHz = FIN * MSEL = 120MHz, so MSEL = 10
           FCCO must be between 156 MHz to 320 MHz, where FCCO = PLL output * 2 * P,
           so P = 1 and FCCO = 120MHz * 2 * 1 = 240MHz */
	Chip_Clock_SetupPLL(SYSCTL_MAIN_PLL, 9, 0);     /* Multiply by 10, Divide by 1 */

	/* Enable PLL0 */
	Chip_Clock_EnablePLL(SYSCTL_MAIN_PLL, SYSCTL_PLL_ENABLE);

	/* Setup USB PLL1 for a 240MHz clock
           Input clock rate (FIN) is main oscillator = 12MHz
           PLL output = 240MHz = FIN * MSEL = 120MHz, so MSEL = 20
           FCCO must be between 156 MHz to 320 MHz, where FCCO = PLL output * 2 * P,
           so P = 1 and FCCO = 240MHz * 2 * 1 = 240MHz */
	Chip_Clock_SetupPLL(SYSCTL_USB_PLL, 19, 0);     /* Multiply by 20, Divide by 1 */

	/* Enable PLL0 */
	Chip_Clock_EnablePLL(SYSCTL_USB_PLL, SYSCTL_PLL_ENABLE);

	/* Since the USB PLL clock is 240MHz, we need to divide by 5 to get 48Mhz
           as needed by the USB peripheral. Also set the USB divider source to
             the USB PLL. USB clock rate = 240 / 5 = 48MHz */
	Chip_Clock_SetUSBClockSource(SYSCTL_USBCLKSRC_USBPLL);
	Chip_Clock_SetUSBClockDiv(5);

	/* PLL1 is disabled until needed */
	Chip_Clock_DisablePLL(SYSCTL_USB_PLL, SYSCTL_PLL_ENABLE);

	/* Wait for main (CPU) PLL0 to lock */
	while ((Chip_Clock_GetPLLStatus(SYSCTL_MAIN_PLL) & SYSCTL_PLLSTS_LOCKED) == 0) {}

	/* The CPU is still sourced from the SYSCLK, so set the CPU divider to
           1 and switch it to the PLL0 clock */
	Chip_Clock_SetCPUClockDiv(1);
	Chip_Clock_SetCPUClockSource(SYSCTL_CCLKSRC_MAINPLL);

	/* Peripheral clocking will be derived from PLL0 with a divider of 2 (60MHz) */
	Chip_Clock_SetPCLKDiv(2);

#if defined(CHIP_LPC407X_8X)
	/* SPIFI clocking will be derived from Main PLL with a divider of 2 (60MHz) */
	Chip_Clock_SetSPIFIClockDiv(2);
	Chip_Clock_SetSPIFIClockSource(SYSCTL_SPIFICLKSRC_MAINPLL);
#endif

}

