/******************************************************************************/
/* TimerDMA -> GPIO                                                  */
/******************************************************************************/
/* This file is part of the uVision/ARM development tools.                    */
/* Copyright (c) 2005-2007 Keil Software. All rights reserved.                */
/* This software may only be used under the terms of a valid, current,        */
/* end user licence from KEIL for a compatible version of KEIL software       */
/* development tools. Nothing else gives you the right to use this software.  */
/******************************************************************************/

#include <LPC17xx.h>
#include "target.h"
#include "it.h"
#include "dma.h"

/***********************************************************************
 *
 * DMA TEST memory parameters
 *
 **********************************************************************/
#define MEMSIZE (97)
#define MEMSTART_U  0x2007C000 		
/**********************************************************************/

/***********************************************************************
 *
 * DMA support functions
 *
 **********************************************************************/
 /*****************************************************************************
** Function name:		clear_mem
**
** Descriptions:		This function fill a block of memory with
**						a specified value
**
** parameters:			Pointer to a starting memory location
**						Memory size
**						The value that the memory should contain
** 						
** Returned value:		None
** 
*****************************************************************************/
void clear_mem(uint8_t *mem, int32_t sz, int32_t value)
{
	uint8_t *addr8;
	int32_t idx;

    addr8 = mem;
    for (idx = 0; idx < sz; idx = idx + 1)
    {
    	*addr8 = (uint8_t) value;
    	addr8++;
    }
}

/*****************************************************************************
** Function name:		fill_mem
**
** Descriptions:		This function will fill a value into a memory location
**						starting at the address pointed by "*mem" with a size
**						of "sz".
**						The value "seed" is shifted by 2 so that it can be
**						displayed onto the LEDs of the MCB1700 dev board
**
** parameters:			Pointer to a starting memory location
**						Memory size
**						The value that the memory should contain, shifted by 2			 
** 						
** Returned value:		None
** 
*****************************************************************************/
void fill_mem(uint8_t *mem, int32_t sz, int32_t seed)
{
	uint8_t *addr8;
	int32_t idx;

    addr8 = mem;
    for (idx = 0; idx < sz; idx = idx + 1)
    {
    	*addr8 = (uint8_t) seed<<2;
    	seed++;
    	addr8++;
    }
}


/***********************************************************************
 *
 * Function: main
 *
 **********************************************************************/
int32_t main (void)
{
  	int32_t dmach, seed, i;

  	TargetResetInit();

 	/* P2.2 to P2.6 defined as Output */
  	GPIO2->FIODIR |= (0x0000007C);

  	/* P1.28, P1.29, and P1.31 defined as Outputs */
  	GPIO1->FIODIR |= (0xB0000000);

  	/* Copy data to FIOPIN using DMA without LLIs   */

  	/* Clear memory */
  	clear_mem((uint8_t *) MEMSTART_U, MEMSIZE, 0);

  	/* Fill memory with data */
  	seed = 0x00;
  	fill_mem((uint8_t *) MEMSTART_U, MEMSIZE, seed);

  	/* Enable Timers (not UARTs) on MUX for DMA Request lines */
	SC->DMAREQSEL = (1<<1);

	/* Initialize DMA */
  	dma_init();
  	dmach = dma_alloc_channel(0, NULL);
  	if (dmach < 0) 
  	{
    	/* "Error allocating DMA channel */
		while(1);
  	}

	/* Clear DMA requests */
	TIM0->IR 	= 0x0F;

  	/* Use DMA to copy the data  */
	dma_start_m2pin(dmach, (void *)(MEMSTART_U),(void *)(&(GPIO2->FIOPIN)), NULL, MEMSIZE);

	/* Program Timer 0 - Match Register 1 */
  	TIM0->MR1 = 12000000-1;
  	TIM0->MCR = (2 << 3);		// Reset on Match MR1
  	TIM0->EMR = (3 << 6);		// Toogle pin
  	TIM0->TCR = 1;		   		// Enable

  	/* Wait for completion and clear terminal count */
  	while (1){

		if ((GPDMA->DMACRawIntTCStat & _BIT(dmach)) == 0)
			GPDMA->DMACIntTCClear = _BIT(dmach);
		i++;
		if (i>1000000) {
			i = 0;
			GPIO1->FIOPIN = ~(GPIO1->FIOPIN) & (1<<28);
		}

		/* INT 0 button is pressed, go into sleep mode */
		if (!(GPIO2->FIOPIN & (1<<10))) {
			/* Go into Sleep mode; using default power save settings */
			__WFI();
		}

  	} 	/* END WHILE(1) */
}		/* END MAIN 	*/
