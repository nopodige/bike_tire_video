/*****************************************************************************
 *   timer.h:  Header file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2008.08.20  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#ifndef __TIMER_H 
#define __TIMER_H

#define TIME_INTERVAL	Fpclk/100 - 1
/* depending on the CCLK and PCLK setting, CCLK = 60Mhz, PCLK = 1/4 CCLK
10mSec = 150.000-1 counts */

void delayMs(uint8_t timer_num, uint32_t delayInMs);
void TIMER0IrqHandler(void);
void TIMER1IrqHandler(void);
void enable_timer(uint8_t timer_num);
void disable_timer(uint8_t timer_num);
void reset_timer(uint8_t timer_num);
void init_timer(uint8_t timer_num, uint32_t timerInterval);

#endif /* end __TIMER_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
