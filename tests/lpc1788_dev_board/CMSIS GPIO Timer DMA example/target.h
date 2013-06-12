/*****************************************************************************
 *   target.h:  Header file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2008.08.20  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#ifndef __TARGET_H 
#define __TARGET_H

#ifdef __cplusplus
   extern "C" {
#endif

#define	USE_USB					1

//This segment should not be modified
#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#if 0
/* Blinky Fail */
/* Fcck = 80Mhz, Fcco = 480Mhz */
#define PLL0_MValue			19
#define PLL0_NValue			0
#define CCLKDivValue		5

#define Fosc	12000000
#define Fcclk	80000000
#define Fcco	480000000
#endif

#if 0
/* Blinky Fail */
/* Fcck = 80Mhz, Fcco = 400Mhz */
#define PLL0_MValue			49
#define PLL0_NValue			2
#define CCLKDivValue		4

#define Fosc	12000000
#define Fcclk	80000000
#define Fcco	400000000
#endif

#if 0
/* Blinky Fail */
/* Fcck = 80Mhz, Fcco = 320Mhz */
#define PLL0_MValue			39
#define PLL0_NValue			2
#define CCLKDivValue		3

#define Fosc	12000000
#define Fcclk	80000000
#define Fcco	320000000
#endif

#if 0
/* Blinky Pass - UART Fail */
/* Fcck = 72Mhz, Fcco = 504Mhz */
#define PLL0_MValue			20
#define PLL0_NValue			0
#define CCLKDivValue		6

#define Fosc	12000000
#define Fcclk	72000000
#define Fcco	504000000
#endif

#if 0
/* Blinky Pass - UART Pass */
/* Fcck = 72Mhz, Fcco = 432Mhz */
#define PLL0_MValue			17
#define PLL0_NValue			0
#define CCLKDivValue		5

#define Fosc	12000000
#define Fcclk	72000000
#define Fcco	432000000
#endif

#if 0
/* Blinky Fail */
/* Fcck = 72Mhz, Fcco = 360Mhz */
#define PLL0_MValue			14
#define PLL0_NValue			0
#define CCLKDivValue		4

#define Fosc	12000000
#define Fcclk	72000000
#define Fcco	360000000
#endif

#if 0
/* Blinky Fail */
/* Fcck = 72Mhz, Fcco = 288Mhz */
#define PLL0_MValue			11
#define PLL0_NValue			0
#define CCLKDivValue		3

#define Fosc	12000000
#define Fcclk	72000000
#define Fcco	288000000
#endif

#if 0
/* Blinky Pass - UART Pass */
/* Fcck = 60Mhz, Fcco = 360Mhz */
#define PLL0_MValue			14
#define PLL0_NValue			0
#define CCLKDivValue		5

#define Fosc	12000000
#define Fcclk	60000000
#define Fcco	360000000
#endif

#if 1
/* Blinky Pass - UART Pass */
/* Fcck = 48Mhz, Fcco = 288Mhz */
#define PLL0_MValue			11
#define PLL0_NValue			0
#define CCLKDivValue		5

#define Fosc	12000000
#define Fcclk	48000000
#define Fcco	288000000
#endif

#if USE_USB
/* Fusb_clk = 48Mhz, Fusb_cco = 192Mhz */
#define PLL1_MValue			3
#define PLL1_PValue			1
#endif

#define Fpclk	(Fcclk / 2)

/******************************************************************************
** Function name:		TargetInit
**
** Descriptions:		Initialize the target board; it is called in a 
**				necessary place, change it as needed
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TargetInit(void);
void ConfigurePLL(void);
void TargetResetInit(void);

#ifdef __cplusplus
   }
#endif
 
#endif /* end __TARGET_H */
/******************************************************************************
**                            End Of File
******************************************************************************/
