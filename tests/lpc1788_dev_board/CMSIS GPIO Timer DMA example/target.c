/*****************************************************************************
 *   target.c:  Target C file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2008.08.20  ver 1.00    Prelimnary version, first Release
 *
*****************************************************************************/
#include <LPC17xx.h>
#include "type.h"
#include "target.h"

/******************************************************************************
** Function name:		TargetInit
**
** Descriptions:		Initialize the target board; it is called in a necessary 
**						place, change it as needed
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void TargetInit(void)
{
  /* Add your codes here */
  return;
}

/******************************************************************************
** Function name:		GPIOResetInit
**
** Descriptions:		Initialize the target board before running the main() 
**				function; User may change it as needed, but may not 
**				deleted it.
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void GPIOResetInit(void)
{
  /* Reset all GPIO pins to default: primary function */
  PINCON->PINSEL0 	= 0x00000000;
  PINCON->PINSEL1 	= 0x00000000;
  PINCON->PINSEL2 	= 0x00000000;
  PINCON->PINSEL3 	= 0x00000000;
  PINCON->PINSEL4 	= 0x00000000;
  PINCON->PINSEL5 	= 0x00000000;
  PINCON->PINSEL6 	= 0x00000000;
  PINCON->PINSEL7 	= 0x00000000;
  PINCON->PINSEL8 	= 0x00000000;
  PINCON->PINSEL9 	= 0x00000000;
  PINCON->PINSEL10 	= 0x00000000;
    
  GPIO0->FIODIR		= 0x00000000;
  GPIO1->FIODIR		= 0x00000000;
  GPIO2->FIODIR		= 0x00000000;
  GPIO3->FIODIR		= 0x00000000;
  GPIO4->FIODIR		= 0x00000000;

  GPIO0->FIOSET		= 0x00000000;
  GPIO1->FIOSET		= 0x00000000;
  GPIO2->FIOSET		= 0x00000000;
  GPIO3->FIOSET		= 0x00000000;
  GPIO4->FIOSET		= 0x00000000;

  return;        
}

/******************************************************************************
** Function name:		ConfigurePLL
**
** Descriptions:		Configure PLL switching to main OSC instead of IRC
**						at power up and wake up from power down. 
**						This routine is used in TargetResetInit() and those
**						examples using power down and wake up such as
**						USB suspend to resume, ethernet WOL, and power management
**						example
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void ConfigurePLL(void)
{
  uint32_t MValue, NValue, PValue;

  if ( SC->PLL0STAT & (1 << 25) )
  {
	SC->PLL0CON = 1;			/* Enable PLL, disconnected */
	SC->PLL0FEED = 0xaa;
	SC->PLL0FEED = 0x55;
  }

  SC->PLL0CON = 0;				/* Disable PLL, disconnected */
  SC->PLL0FEED = 0xaa;
  SC->PLL0FEED = 0x55;
    
  SC->SCS |= 0x20;			/* Enable main OSC */
  while( !(SC->SCS & 0x40) );	/* Wait until main OSC is usable */

  SC->CLKSRCSEL = 0x1;		/* select main OSC, 12MHz, as the PLL clock source */

  SC->PLL0CFG = PLL0_MValue | (PLL0_NValue << 16);
  SC->PLL0FEED = 0xaa;
  SC->PLL0FEED = 0x55;
      
  SC->PLL0CON = 1;				/* Enable PLL, disconnected */
  SC->PLL0FEED = 0xaa;
  SC->PLL0FEED = 0x55;

  SC->CCLKCFG = CCLKDivValue;	/* Set clock divider */

  while ( ((SC->PLL0STAT & (1 << 26)) == 0) );	/* Check lock bit status */
    
  MValue = SC->PLL0STAT & 0x00007FFF;
  NValue = (SC->PLL0STAT & 0x00FF0000) >> 16;
  while ((MValue != PLL0_MValue) && ( NValue != PLL0_NValue) );

  SC->PLL0CON = 3;				/* enable and connect */
  SC->PLL0FEED = 0xaa;
  SC->PLL0FEED = 0x55;
  while ( ((SC->PLL0STAT & (1 << 25)) == 0) );	/* Check connect bit status */

#if USE_USB
  if ( SC->PLL1STAT & (1 << 9) )
  {
	SC->PLL1CON = 1;			/* Enable PLL, disconnected */
	SC->PLL1FEED = 0xaa;
	SC->PLL1FEED = 0x55;
  }

  SC->PLL1CON = 0;				/* Disable PLL, disconnected */
  SC->PLL1FEED = 0xaa;
  SC->PLL1FEED = 0x55;

  SC->PLL1CFG = PLL1_MValue | (PLL1_PValue << 5);
  SC->PLL1FEED = 0xaa;
  SC->PLL1FEED = 0x55;
      
  SC->PLL1CON = 1;				/* Enable PLL, disconnected */
  SC->PLL1FEED = 0xaa;
  SC->PLL1FEED = 0x55;
  while ( ((SC->PLL1STAT & (1 << 10)) == 0) );	/* Check lock bit status */

  MValue = SC->PLL1STAT & 0x0000001F;
  PValue = (SC->PLL1STAT & 0x00000060) >> 5;
  while ((MValue != PLL1_MValue) && ( PValue != PLL1_PValue) );

  SC->PLL1CON = 3;				/* enable and connect */
  SC->PLL1FEED = 0xaa;
  SC->PLL1FEED = 0x55;
  while ( ((SC->PLL1STAT & (1 << 9)) == 0) );	/* Check connect bit status */
#endif

  return;
}

/******************************************************************************
** Function name:		TargetResetInit
**
** Descriptions:		Initialize the target board before running the main() 
**						function; User may change it as needed, but may not 
**						deleted it.
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void TargetResetInit(void)
{
#if USE_USB
//  PCONP |= 0x80000000;		/* Turn On USB PCLK */
#endif
  /* Configure PLL, switch from IRC to Main OSC */
  ConfigurePLL();

  /* Set system timers for each component */
#if (Fpclk / (Fcclk / 4)) == 1
  SC->PCLKSEL0 = 0x00000000;	/* PCLK is 1/4 CCLK */
  SC->PCLKSEL1 = 0x00000000;
#endif
#if (Fpclk / (Fcclk / 4)) == 2
  SC->PCLKSEL0 = 0xAAAAAAAA;	/* PCLK is 1/2 CCLK */
  SC->PCLKSEL1 = 0xAAAAAAAA;	 
#endif
#if (Fpclk / (Fcclk / 4)) == 4
  SC->PCLKSEL0 = 0x55555555;	/* PCLK is the same as CCLK */
  SC->PCLKSEL1 = 0x55555555;	
#endif

  GPIOResetInit();

  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
