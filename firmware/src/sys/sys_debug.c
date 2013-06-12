/**
 * \name sys_debug.c 
 *
 * \author Reed
 * \date Jun 12, 2013
 *
 * \brief
 *
 * \desc
 *
 */


#include "common.h"



/* Initialize debug output via UART for board */
void sys_debug_init(void)
{
  /*
   * Initialize UART0 pin connect
   * P0.2: TXD
   * P0.3: RXD
   */
  Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 2, (IOCON_FUNC1 | IOCON_MODE_INACT));
  Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 3, (IOCON_FUNC1 | IOCON_MODE_INACT));

  Chip_UART_Init(DEBUG_UART);
  Chip_UART_SetBaud(DEBUG_UART, 115200);
  Chip_UART_ConfigData(DEBUG_UART, UART_DATABIT_8, UART_PARITY_NONE, UART_STOPBIT_1);

  /* Enable UART Transmit */
  Chip_UART_TxCmd(DEBUG_UART, ENABLE);

}
