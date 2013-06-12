/*
 * WS2811_driver.S
 *
 *  Created on: Jun 9, 2013
 *      Author: Reed
 */


.syntax unified
.thumb_func
 .global WS2811_sendData


 .equ WAIT_HIGH, 9
 .equ WAIT_DATA, 28
 .equ WAIT_LOW, 8
 .equ WAIT_HOLD, 60

 .type   WS2811_sendData, %function

 /**
  *
  */
WS2811_sendData:
    push {r4,r5,r6}
    mov r3, 0
    mov r4, 0xFF

.WS2811_sendData_loop:
    subs r1, #1
    blt .WS2811_sendData_end
    strb r4, [r2]
    mov r5, WAIT_HIGH
.WS2811_sendData_Wait_High:
    subs r5, #1
    bgt .WS2811_sendData_Wait_High
    ldr r6, [r0], #1
    strb r6, [r2]
    mov r5, WAIT_DATA
.WS2811_sendData_Wait_Data:
    subs r5, #1
    bgt .WS2811_sendData_Wait_Data
    strb r3, [r2]
    mov r5, WAIT_LOW
.WS2811_sendData_Wait_Low:
    subs r5, #1
    bgt .WS2811_sendData_Wait_Low
    b .WS2811_sendData_loop

.WS2811_sendData_end:
    strb r3, [r2]
    mov r5, 255
    add r5,347
.WS2811_sendData_Wait_Hold:
    subs r5, #1
    bgt .WS2811_sendData_Wait_Hold
    pop {r4,r5,r6}
    bx lr
    nop
