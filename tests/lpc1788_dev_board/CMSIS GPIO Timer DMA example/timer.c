/*****************************************************************************
 *   timer.c:  Timer C file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2008.08.20  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include <LPC17xx.h>
#include "type.h"
#include "target.h"
#include "it.h"
#include "timer.h"

volatile uint32_t timer0_counter = 0;
volatile uint32_t timer1_counter = 0;

/*****************************************************************************
** Function name:		delayMs
**
** Descriptions:		Start the timer delay in milo seconds
**						until elapsed
**
** parameters:			timer number, Delay value in milo second			 
** 						
** Returned value:		None
** 
*****************************************************************************/
void delayMs(uint8_t timer_num, uint32_t delayInMs)
{
  if (timer_num == 0)
  {
    /*
    * setup timer #0 for delay
    */
    TIM0->TCR = 0x02;		/* reset timer */
    TIM0->PR  = 0x00;		/* set prescaler to zero */
    TIM0->MR0 = delayInMs * (Fpclk / 1000);
    TIM0->IR  = 0xff;		/* reset all interrrupts */
    TIM0->MCR = 0x04;		/* stop timer on match */
    TIM0->TCR = 0x01;		/* start timer */
  
    /* wait until delay time has elapsed */
    while (TIM0->TCR & 0x01);
  }
  else if (timer_num == 1)
  {
    /*
    * setup timer #1 for delay
    */
    TIM1->TCR = 0x02;		/* reset timer */
    TIM1->PR  = 0x00;		/* set prescaler to zero */
    TIM1->MR0 = delayInMs * (Fpclk / 1000);
    TIM1->IR  = 0xff;		/* reset all interrrupts */
    TIM1->MCR = 0x04;		/* stop timer on match */
    TIM1->TCR = 0x01;		/* start timer */
  
    /* wait until delay time has elapsed */
    while (TIM1->TCR & 0x01);
  }
  return;
}

/******************************************************************************
** Function name:		TIMER0IrqHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**						executes each 10ms @ 60 MHz CPU Clock
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void TIMER0IrqHandler(void)
{  
  	TIM0->IR = 1;			/* clear interrupt flag */
//  IENABLE;			/* handles nested interrupt */

  	timer0_counter++;
//  IDISABLE;
}

/******************************************************************************
** Function name:		TIMER1IrqHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**						executes each 10ms @ 60 MHz CPU Clock
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void TIMER1IrqHandler(void)
{  
  	TIM1->IR = 1;			/* clear interrupt flag */
//  IENABLE;			/* handles nested interrupt */

  	timer1_counter++;
//  IDISABLE;
}

/******************************************************************************
** Function name:		enable_timer
**
** Descriptions:		Enable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
** 
******************************************************************************/
void enable_timer(uint8_t timer_num)
{
  if ( timer_num == 0 )
  {
    TIM0->TCR = 1;
  }
  else
  {
    TIM1->TCR = 1;
  }
  return;
}

/******************************************************************************
** Function name:		disable_timer
**
** Descriptions:		Disable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
** 
******************************************************************************/
void disable_timer(uint8_t timer_num)
{
  if ( timer_num == 0 )
  {
    TIM0->TCR = 0;
  }
  else
  {
    TIM1->TCR = 0;
  }
  return;
}

/******************************************************************************
** Function name:		reset_timer
**
** Descriptions:		Reset timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
** 
******************************************************************************/
void reset_timer(uint8_t timer_num)
{
  uint32_t regVal;

  if ( timer_num == 0 )
  {
    regVal = TIM0->TCR;
    regVal |= 0x02;
    TIM0->TCR = regVal;
  }
  else
  {
    regVal = TIM1->TCR;
    regVal |= 0x02;
    TIM1->TCR = regVal;
  }
  return;
}

/******************************************************************************
** Function name:		init_timer
**
** Descriptions:		Initialize timer, set timer interval, reset timer,
**						install timer interrupt handler
**
** parameters:			timer number and timer interval
** Returned value:		None
** 
******************************************************************************/
void init_timer(uint8_t timer_num, uint32_t TimerInterval) 
{
//  NVIC_InitTypeDef NVIC_InitStructure;

  if ( timer_num == 0 )
  {
    timer0_counter = 0;
    TIM0->MR0 = TimerInterval;
    TIM0->MCR = 3;				/* Interrupt and Reset on MR0 */

    /* Enable the TIMER0 Interrupt */
	/* Not needed in this project */
	/*
    NVIC_InitStructure.NVIC_IRQChannel = TIMER0_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.cb = (PFV)TIMER0IrqHandler;
    NVIC_Init(&NVIC_InitStructure);
	*/
  }
  else if ( timer_num == 1 )
  {
    timer1_counter = 0;
    TIM1->MR0 = TimerInterval;
    TIM1->MCR = 3;				/* Interrupt and Reset on MR1 */

    /* Enable the TIMER1 Interrupt */
	/* Not needed in this project */
	/*
    NVIC_InitStructure.NVIC_IRQChannel = TIMER1_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.cb = (PFV)TIMER1IrqHandler;
    NVIC_Init(&NVIC_InitStructure);
	*/
  }
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
