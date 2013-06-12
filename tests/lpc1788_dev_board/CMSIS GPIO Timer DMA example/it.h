/******************************************************************************
 *   it.h:  Header file for NXP LPC17xx Family 
 *   Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2008.08.21  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#ifndef __IT_H 
#define __IT_H

/* IRQ Channels --------------------------------------------------------------*/
#define WDT_IRQChannel               (0x00)  /* Watchdog Interrupt (WDINT) */
#define TIMER0_IRQChannel            (0x01)  /* Match 0 - 1 (MR0, MR1)
                                                Capture 0 - 1 (CR0, CR1) */
#define TIMER1_IRQChannel            (0x02)  /* Match 0 - 2 (MR0, MR1, MR2)
                                                Capture 0 - 1 (CR0, CR1) */
#define TIMER2_IRQChannel            (0x03)  /* Match 0-3
                                                Capture 0-1 */
#define TIMER3_IRQChannel            (0x04)  /* Match 0-3
                                                Capture 0-1 */
#define UART0_IRQChannel             (0x05)  /* Rx Line Status (RLS)
                                                Transmit Holding Register Empty (THRE)
                                                Rx Data Available (RDA)
                                                Character Time-out Indicator (CTI)
                                                End of Auto-Baud (ABEO)
                                                Auto-Baud Time-Out (ABTO) */
#define UART1_IRQChannel             (0x06)  /* Rx Line Status (RLS)
                                                Transmit Holding Register Empty (THRE)
                                                Rx Data Available (RDA)
                                                Character Time-out Indicator (CTI)
                                                Modem Control Change
                                                End of Auto-Baud (ABEO)
                                                Auto-Baud Time-Out (ABTO) */
#define UART2_IRQChannel             (0x07)  /* Rx Line Status (RLS)
                                                Transmit Holding Register Empty (THRE)
                                                Rx Data Available (RDA)
                                                Character Time-out Indicator (CTI)
                                                End of Auto-Baud (ABEO)
                                                Auto-Baud Time-Out (ABTO) */
#define UART3_IRQChannel             (0x08)  /* Rx Line Status (RLS)
                                                Transmit Holding Register Empty (THRE)
                                                Rx Data Available (RDA)
                                                Character Time-out Indicator (CTI)
                                                End of Auto-Baud (ABEO)
                                                Auto-Baud Time-Out (ABTO) */
#define PWM1_IRQChannel              (0x09)  /* Match 0 - 6 of PWM1
                                                Capture 0-1 of PWM1 */
#define I2C0_IRQChannel              (0x0A)  /* SI (state change) */
#define I2C1_IRQChannel              (0x0B)  /* SI (state change) */
#define I2C2_IRQChannel              (0x0C)  /* SI (state change) */
#define SPI_IRQChannel               (0x0D)  /* SPI Interrupt Flag (SPIF)
                                                Mode Fault (MODF) */
#define SSP0_IRQChannel              (0x0E)  /* Tx FIFO half empty of SSP0
                                                Rx FIFO half full of SSP0
                                                Rx Timeout of SSP0
                                                Rx Overrun of SSP0 */
#define SSP1_IRQChannel              (0x0F)  /* Tx FIFO half empty of SSP1
                                                Rx FIFO half full of SSP1
                                                Rx Timeout of SSP1
                                                Rx Overrun of SSP1 */
#define PLL0_IRQChannel              (0x10)  /* PLL0 Lock (PLOCK0) */
#define RTC_IRQChannel               (0x11)  /* Counter Increment (RTCCIF)
                                                Alarm (RTCALF) */
#define EINT0_IRQChannel             (0x12)  /* External Interrupt 0 (EINT0) */
#define EINT1_IRQChannel             (0x13)  /* External Interrupt 1 (EINT1) */
#define EINT2_IRQChannel             (0x14)  /* External Interrupt 2 (EINT2) */
#define EINT3_IRQChannel             (0x15)  /* External Interrupt 3 (EINT3)
                                                Note: EINT3 channel is shared with GPIO interrupts */
#define ADC_IRQChannel               (0x16)  /* A/D Converter end of conversion */
#define BOD_IRQChannel               (0x17)  /* Brown Out detect */
#define USB_IRQChannel               (0x18)  /* USB_INT_REQ_LP
                                                USB_INT_REQ_HP
                                                USB_INT_REQ_DMA */
#define CAN_IRQChannel               (0x19)  /* CAN Common
                                                CAN 0 Tx
                                                CAN 0 Rx
                                                CAN 1 Tx
                                                CAN 1 Rx */
#define DMA_IRQChannel               (0x1A)  /* IntStatus of DMA channel 0
                                                IntStatus of DMA channel 1 */
#define I2S_IRQChannel               (0x1B)  /* irq
                                                dmareq1
                                                dmareq2 */
#define ENET_IRQChannel              (0x1C)  /* WakeupInt
                                                SoftInt
                                                TxDoneInt
                                                TxFinishedInt
                                                TxErrorInt
                                                TxUnderrunInt
                                                RxDoneInt
                                                RxFinishedInt
                                                RxErrorInt
                                                RxOverrunInt */
#define RIT_IRQChannel               (0x1D)  /* OSTINT */
#define MCPWM_IRQChannel             (0x1E)  /* IPER[2:0]
                                                IPW[2:0]
                                                ICAP[2:0]
                                                FES */
#define QEI_IRQChannel               (0x1F)  /* INX_Int
                                                TIM_Int
                                                VELC_Int
                                                DIR_Int
                                                ERR_Int
                                                ENCLK_Int
                                                POS0_Int
                                                POS1_Int
                                                POS2_Int
                                                REV_Int
                                                POS0REV_Int
                                                POS1REV_Int
                                                POS2REV_Int */
#define PLL1_IRQChannel              (0x20)  /* PLL1 Lock (PLOCK1) */

#define MAX_IRQChannel               (0x21)

/* Exported functions ------------------------------------------------------- */
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void WDT_IRQHandler(void);
void TIMER0_IRQHandler(void);
void TIMER1_IRQHandler(void);
void TIMER2_IRQHandler(void);
void TIMER3_IRQHandler(void);
void UART0_IRQHandler(void);
void UART1_IRQHandler(void);
void UART2_IRQHandler(void);
void UART3_IRQHandler(void);
void PWM1_IRQHandler(void);
void I2C0_IRQHandler(void);
void I2C1_IRQHandler(void);
void I2C2_IRQHandler(void);
void SPI_IRQHandler(void);
void SSP0_IRQHandler(void);
void SSP1_IRQHandler(void);
void PLL0_IRQHandler(void);
void RTC_IRQHandler(void);
void EINT0_IRQHandler(void);
void EINT1_IRQHandler(void);
void EINT2_IRQHandler(void);
void EINT3_IRQHandler(void);
void ADC_IRQHandler(void);
void BOD_IRQHandler(void);
void USB_IRQHandler(void);
void CAN_IRQHandler(void);
void DMA_IRQHandler(void);
void I2S_IRQHandler(void);
void ENET_IRQHandler(void);
void RIT_IRQHandler(void);
void MCPWM_IRQHandler(void);
void QEI_IRQHandler(void);
void PLL1_IRQHandler(void);
					 
#endif /* end __IT_H */

/******************************************************************************
**                            End Of File
******************************************************************************/
