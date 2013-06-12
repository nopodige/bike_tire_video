/*****************************************************************************
 *   it.c: ISR C file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2008.08.21  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include <LPC17xx.h>
#include "type.h"
#include "it.h"
/* Not needed in this project */
//#include "systick.h"


volatile PFV cb [MAX_IRQChannel];

/*******************************************************************************
* Function Name  : NMI_Handler
* Description    : This function handles NMI exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NMI_Handler(void)
{
}

/*******************************************************************************
* Function Name  : HardFault_Handler
* Description    : This function handles Hard Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : MemManage_Handler
* Description    : This function handles Memory Manage exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : BusFault_Handler
* Description    : This function handles Bus Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : UsageFault_Handler
* Description    : This function handles Usage Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : SVC_Handler
* Description    : This function handles SVCall exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SVC_Handler(void)
{
}

/*******************************************************************************
* Function Name  : DebugMon_Handler
* Description    : This function handles Debug Monitor exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DebugMon_Handler(void)
{
}

/*******************************************************************************
* Function Name  : PendSV_Handler
* Description    : This function handles PendSVC exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PendSV_Handler(void)
{
}

/*******************************************************************************
* Function Name  : SysTick_Handler
* Description    : This function handles SysTick Handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTick_Handler(void)
{
	/* Not needed in this project */
	//SysTickHandler();
}

/*******************************************************************************
* Function Name  : WDT_IRQHandler
* Description    : This function handles WDT interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void WDT_IRQHandler(void)
{
  if (cb[WDT_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[WDT_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : TIMER0_IRQHandler
* Description    : This function handles TIMER0 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIMER0_IRQHandler(void)
{
  if (cb[TIMER0_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[TIMER0_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : TIMER1_IRQHandler
* Description    : This function handles TIMER1 interrupt request. 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIMER1_IRQHandler(void)
{
  if (cb[TIMER1_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[TIMER1_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : TIMER2_IRQHandler
* Description    : This function handles TIMER2 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIMER2_IRQHandler(void)
{
  if (cb[TIMER2_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[TIMER2_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : TIMER3_IRQHandler
* Description    : This function handles TIMER3 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIMER3_IRQHandler(void)
{
  if (cb[TIMER3_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[TIMER3_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : UART0_IRQHandler
* Description    : This function handles UART0 interrupt request. 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART0_IRQHandler(void)
{
  if (cb[UART0_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[UART0_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : UART1_IRQHandler
* Description    : This function handles UART1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART1_IRQHandler(void)
{
  if (cb[UART1_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[UART1_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : UART2_IRQHandler
* Description    : This function handles UART2 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART2_IRQHandler(void)
{
  if (cb[UART2_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[UART2_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : UART3_IRQHandler
* Description    : This function handles UART3 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART3_IRQHandler(void)
{
  if (cb[UART3_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[UART3_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : PWM1_IRQHandler
* Description    : This function handles PWM1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PWM1_IRQHandler(void)
{
  if (cb[PWM1_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[PWM1_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : I2C0_IRQHandler
* Description    : This function handles I2C0 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C0_IRQHandler(void)
{
  if (cb[I2C0_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[I2C0_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : I2C1_IRQHandler
* Description    : This function handles I2C1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C1_IRQHandler(void)
{
  if (cb[I2C1_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[I2C1_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : I2C2_IRQHandler
* Description    : This function handles I2C2 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C2_IRQHandler(void)
{
  if (cb[I2C2_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[I2C2_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : SPI_IRQHandler
* Description    : This function handles SPI interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_IRQHandler(void)
{
  if (cb[SPI_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[SPI_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : SSP0_IRQHandler
* Description    : This function handles SSP0 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SSP0_IRQHandler(void)
{
  if (cb[SSP0_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[SSP0_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : SSP1_IRQHandler
* Description    : This function handles SSP1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SSP1_IRQHandler(void)
{
  if (cb[SSP1_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[SSP1_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : PLL0_IRQHandler
* Description    : This function handles PLL0 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PLL0_IRQHandler(void)
{
  if (cb[PLL0_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[PLL0_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : RTC_IRQHandler
* Description    : This function handles RTC interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_IRQHandler(void)
{
  if (cb[RTC_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[RTC_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : EINT0_IRQHandler
* Description    : This function handles EINT0 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EINT0_IRQHandler(void)
{
  if (cb[EINT0_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[EINT0_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : EINT1_IRQHandler
* Description    : This function handles EINT1 interrupt request. 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EINT1_IRQHandler(void)
{
  if (cb[EINT1_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[EINT1_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : EINT2_IRQHandler
* Description    : This function handles EINT2 interrupt request. 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EINT2_IRQHandler(void)
{
  if (cb[EINT2_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[EINT2_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : EINT3_IRQHandler
* Description    : This function handles EINT3 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EINT3_IRQHandler(void)
{
  if (cb[EINT3_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[EINT3_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : ADC_IRQHandler
* Description    : This function handles ADC interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_IRQHandler(void)
{
  if (cb[ADC_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[ADC_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : BOD_IRQHandler
* Description    : This function handles BOD interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BOD_IRQHandler(void)
{
  if (cb[BOD_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[BOD_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : USB_IRQHandler
* Description    : This function handles USB interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_IRQHandler(void)
{
  if (cb[USB_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[USB_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : CAN_IRQHandler
* Description    : This function handles CAN interrupt request. 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN_IRQHandler(void)
{
  if (cb[CAN_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[CAN_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : DMA_IRQHandler
* Description    : This function handles GPDMA interrupt request. 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA_IRQHandler(void)
{
  if (cb[DMA_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[DMA_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : I2S_IRQHandler
* Description    : This function handles I2S interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2S_IRQHandler(void)
{
  if (cb[I2S_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[I2S_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : ENET_IRQHandler
* Description    : This function handles ETHERNET interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ENET_IRQHandler(void)
{
  if (cb[ENET_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[ENET_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : RIT_IRQHandler
* Description    : This function handles Repetitive Interrupt Timer interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RIT_IRQHandler(void)
{
  if (cb[RIT_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[RIT_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : MCPWM_IRQHandler
* Description    : This function handles MCPWM interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MCPWM_IRQHandler(void)
{
  if (cb[MCPWM_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[MCPWM_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : QEI_IRQHandler
* Description    : This function handles QEI interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void QEI_IRQHandler(void)
{
  if (cb[QEI_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[QEI_IRQChannel]();
  }
}

/*******************************************************************************
* Function Name  : PLL1_IRQHandler
* Description    : This function handles PLL1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PLL1_IRQHandler(void)
{
  if (cb[PLL1_IRQChannel] != NULL)
  {
    /* Call user defined callback function */
    cb[PLL1_IRQChannel]();
  }
}

/******************************************************************************
**                            End Of File
******************************************************************************/
