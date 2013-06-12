/*
 * doWait.S
 *
 *  Created on: May 26, 2013
 *      Author: Reed
 */


.syntax unified
.thumb_func
 .global doWait

doWait:
   subs r0,#1
   bne doWait
   bx lr
