;/*****************************************************************************
;*   vector.s: Vector file for NXP LPC17xx Family Microprocessors
;*
;*   Copyright(C) 2008, NXP Semiconductor
;*   All rights reserved.
;*
;*   History
;*   2008.08.21  ver 1.00    Prelimnary version, first Release
;*
;*****************************************************************************/

; Amount of memory (in bytes) allocated for Stack and Heap
; Tailor those values to your application needs
;// <h> Stack Configuration
;//   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
;// </h>

Stack_Size       EQU     0x00000400

                 AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem        SPACE   Stack_Size
__initial_sp


;// <h> Heap Configuration
;//   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
;// </h>

Heap_Size        EQU     0x00000200

                 AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem         SPACE   Heap_Size
__heap_limit

  
                 THUMB
                 PRESERVE8

                 ; Import exceptions handlers
                 IMPORT  NMI_Handler
                 IMPORT  HardFault_Handler
                 IMPORT  MemManage_Handler
                 IMPORT  BusFault_Handler
                 IMPORT  UsageFault_Handler
                 IMPORT  SVC_Handler
                 IMPORT  DebugMon_Handler
                 IMPORT  PendSV_Handler
                 IMPORT  SysTick_Handler
                 IMPORT  WDT_IRQHandler
                 IMPORT  TIMER0_IRQHandler
                 IMPORT  TIMER1_IRQHandler
                 IMPORT  TIMER2_IRQHandler
                 IMPORT  TIMER3_IRQHandler
                 IMPORT  UART0_IRQHandler
                 IMPORT  UART1_IRQHandler
                 IMPORT  UART2_IRQHandler
                 IMPORT  UART3_IRQHandler
                 IMPORT  PWM1_IRQHandler
                 IMPORT  I2C0_IRQHandler
                 IMPORT  I2C1_IRQHandler
                 IMPORT  I2C2_IRQHandler
                 IMPORT  SPI_IRQHandler
                 IMPORT  SSP0_IRQHandler
                 IMPORT  SSP1_IRQHandler
                 IMPORT  PLL0_IRQHandler
                 IMPORT  RTC_IRQHandler
                 IMPORT  EINT0_IRQHandler
                 IMPORT  EINT1_IRQHandler
                 IMPORT  EINT2_IRQHandler
                 IMPORT  EINT3_IRQHandler
                 IMPORT  ADC_IRQHandler
                 IMPORT  BOD_IRQHandler
                 IMPORT  USB_IRQHandler
                 IMPORT  CAN_IRQHandler
                 IMPORT  DMA_IRQHandler
                 IMPORT  I2S_IRQHandler
                 IMPORT  ENET_IRQHandler
                 IMPORT  RIT_IRQHandler
                 IMPORT  MCPWM_IRQHandler
                 IMPORT  QEI_IRQHandler
                 IMPORT  PLL1_IRQHandler

;*******************************************************************************
; Fill-up the Vector Table entries with the exceptions ISR address
;*******************************************************************************
                 AREA    RESET, DATA, READONLY
                 EXPORT  __Vectors
                      
__Vectors        DCD  __initial_sp              ; Top of Stack
                 DCD  Reset_Handler
                 DCD  NMI_Handler
                 DCD  HardFault_Handler
                 DCD  MemManage_Handler
                 DCD  BusFault_Handler
                 DCD  UsageFault_Handler
                 DCD  0                 ; Reserved
                 DCD  0                 ; Reserved
                 DCD  0                 ; Reserved
                 DCD  0                 ; Reserved
                 DCD  SVC_Handler
                 DCD  DebugMon_Handler
                 DCD  0                 ; Reserved
                 DCD  PendSV_Handler
                 DCD  SysTick_Handler
                 DCD  WDT_IRQHandler
                 DCD  TIMER0_IRQHandler
                 DCD  TIMER1_IRQHandler
                 DCD  TIMER2_IRQHandler
                 DCD  TIMER3_IRQHandler
                 DCD  UART0_IRQHandler
                 DCD  UART1_IRQHandler
                 DCD  UART2_IRQHandler
                 DCD  UART3_IRQHandler
                 DCD  PWM1_IRQHandler
                 DCD  I2C0_IRQHandler
                 DCD  I2C1_IRQHandler
                 DCD  I2C2_IRQHandler
                 DCD  SPI_IRQHandler
                 DCD  SSP0_IRQHandler
                 DCD  SSP1_IRQHandler
                 DCD  PLL0_IRQHandler
                 DCD  RTC_IRQHandler
                 DCD  EINT0_IRQHandler
                 DCD  EINT1_IRQHandler
                 DCD  EINT2_IRQHandler
                 DCD  EINT3_IRQHandler
                 DCD  ADC_IRQHandler
                 DCD  BOD_IRQHandler
                 DCD  USB_IRQHandler
                 DCD  CAN_IRQHandler
                 DCD  DMA_IRQHandler
                 DCD  I2S_IRQHandler
                 DCD  ENET_IRQHandler
                 DCD  RIT_IRQHandler
                 DCD  MCPWM_IRQHandler
                 DCD  QEI_IRQHandler
                 DCD  PLL1_IRQHandler

                 AREA    |.text|, CODE, READONLY

; Reset handler routine
Reset_Handler    PROC
                 EXPORT  Reset_Handler
                 IMPORT  __main
                 LDR     R0, =__main
                 BX      R0
                 ENDP

                 ALIGN

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
                 IF      :DEF:__MICROLIB
                
                 EXPORT  __initial_sp
                 EXPORT  __heap_base
                 EXPORT  __heap_limit
                
                 ELSE
                
                 IMPORT  __use_two_region_memory
                 EXPORT  __user_initial_stackheap
__user_initial_stackheap

                 LDR     R0, =  Heap_Mem
                 LDR     R1, =(Stack_Mem + Stack_Size)
                 LDR     R2, = (Heap_Mem +  Heap_Size)
                 LDR     R3, = Stack_Mem
                 BX      LR

                 ALIGN

                 ENDIF

                 END
