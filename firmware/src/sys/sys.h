/**
 * \name sys.h 
 *
 * \author Reed
 * \date Jun 12, 2013
 *
 * \brief
 *
 * \desc
 *
 */
#ifndef _SYS_H_
#define _SYS_H_


#include "chip.h"


#define DEBUG_PRINTF(fmt, ...) printf(fmt, ## __VA_ARGS__)
#define DEBUG_PRINT(fmt) sys_putstr(fmt)
#define DEBUG_PUTCH(c) sys_putch(c)


#define ENABLE_INTERRUPTS() __enable_irq()
#define DISABLE_INTERRUPTS() __disable_irq()



/**************************************************************************************************
 * \brief
 *
 * \param
 * \return
 */
void sys_init();


/**************************************************************************************************
 * \brief Sends a character on the UART
 *
 * \param
 * \return
 */
static inline void sys_putch(char ch)
{
  while (Chip_UART_SendByte(DEBUG_UART, (uint8_t) ch) == ERROR) {}
}

/**************************************************************************************************
 * \brief Gets a character from the UART, returns EOF if no character is ready
 *
 * \param
 * \return
 */
static inline int sys_getch(void)
{
  uint8_t data;

  if (Chip_UART_ReceiveByte(DEBUG_UART, &data) == SUCCESS)
    {
      return (int) data;
    }

  return -1;
}

/**************************************************************************************************
 * \brief Outputs a string on the debug UART
 *
 * \param
 * \return
 */
static inline void sys_putstr(char *str)
{
  while (*str != '\0')
    {
      sys_putch(*str++);
    }

}



#endif /* _SYS_H_ */
