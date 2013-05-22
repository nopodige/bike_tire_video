/*
 * @brief LPC8xx Switch Matrix driver
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef __SWM_8XX_H_
#define __SWM_8XX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup SWM_8XX CHIP: LPC8xx Switch Matrix Driver
 * @ingroup CHIP_8XX_Drivers
 * @{
 */

/**
 * @brief LPC8XX Switch Matrix register block structure
 */
typedef struct {
	__IO uint32_t PINASSIGN[9];		/*!< Pin Assign register array */
	__I  uint32_t RESERVED0[103];
	__IO uint32_t PINENABLE0;		/*!< Pin Enable register */
} LPC_SWM_T;

/**
 * @brief LPC8XX Switch Matrix Movable pins
 */
typedef enum CHIP_SWM_PIN_MOVABLE  {
	SWM_U0_TXD_O        = 0x00,	/*!< PINASSIGN0 - UART0 TXD Output */
	SWM_U0_RXD_I        = 0x01,	/*!< PINASSIGN0 - UART0 RXD Input */
	SWM_U0_RTS_O        = 0x02,	/*!< PINASSIGN0 - UART0 RTS Output */
	SWM_U0_CTS_I        = 0x03,	/*!< PINASSIGN0 - UART0 CTS Input */
	SWM_U0_SCLK_IO      = 0x10,	/*!< PINASSIGN1 - UART0 SCLK I/O */
	SWM_U1_TXD_O        = 0x11,	/*!< PINASSIGN1 - UART1 TXD Output */
	SWM_U1_RXD_I        = 0x12,	/*!< PINASSIGN1 - UART1 RXD Input */
	SWM_U1_RTS_O        = 0x13,	/*!< PINASSIGN1 - UART1 RTS Output */
	SWM_U1_CTS_I        = 0x20,	/*!< PINASSIGN2 - UART1 CTS Input */
	SWM_U1_SCLK_IO      = 0x21,	/*!< PINASSIGN2 - UART1 SCLK I/O */
	SWM_U2_TXD_O        = 0x22,	/*!< PINASSIGN2 - UART2 TXD Output */
	SWM_U2_RXD_I        = 0x23,	/*!< PINASSIGN2 - UART2 RXD Input */
	SWM_U2_RTS_O        = 0x30,	/*!< PINASSIGN3 - UART2 RTS Output */
	SWM_U2_CTS_I        = 0x31,	/*!< PINASSIGN3 - UART2 CTS Input */
	SWM_U2_SCLK_IO      = 0x32,	/*!< PINASSIGN3 - UART2 SCLK I/O */
	SWM_SPI0_SCK_IO     = 0x33,	/*!< PINASSIGN3 - SPI0 SCK I/O */
	SWM_SPI0_MOSI_IO    = 0x40,	/*!< PINASSIGN4 - SPI0 MOSI I/O */
	SWM_SPI0_MISO_IO    = 0x41,	/*!< PINASSIGN4 - SPI0 MISO I/O */
	SWM_SPI0_SSEL_IO    = 0x42,	/*!< PINASSIGN4 - SPI0 SSEL I/O */
	SWM_SPI1_SCK_IO     = 0x43,	/*!< PINASSIGN4 - SPI1 SCK I/O */
	SWM_SPI1_MOSI_IO    = 0x50,	/*!< PINASSIGN5 - SPI1 MOSI I/O */
	SWM_SPI1_MISO_IO    = 0x51,	/*!< PINASSIGN5 - SPI1 MISO I/O */
	SWM_SPI1_SSEL_IO    = 0x52,	/*!< PINASSIGN5 - SPI1 SSEL I/O */
	SWM_CTIN_0_I        = 0x53,	/*!< PINASSIGN5 - CTIN0 Input */
	SWM_CTIN_1_I        = 0x60,	/*!< PINASSIGN6 - CTIN1 Input */
	SWM_CTIN_2_I        = 0x61,	/*!< PINASSIGN6 - CTIN2 Input */
	SWM_CTIN_3_I        = 0x62,	/*!< PINASSIGN6 - CTIN3 Input */
	SWM_CTOUT_0_O       = 0x63,	/*!< PINASSIGN6 - CTOUT0 Output */
	SWM_CTOUT_1_O       = 0x70,	/*!< PINASSIGN7 - CTOUT1 Output */
	SWM_CTOUT_2_O       = 0x71,	/*!< PINASSIGN7 - CTOUT2 Output */
	SWM_CTOUT_3_O       = 0x72,	/*!< PINASSIGN7 - CTOUT3 Output */
	SWM_I2C_SDA_IO      = 0x73,	/*!< PINASSIGN7 - I2C SDA I/O */
	SWM_I2C_SCL_IO      = 0x80,	/*!< PINASSIGN8 - I2C SCL I/O */
	SWM_ACMP_O_O        = 0x81,	/*!< PINASSIGN8 - I2C ACMP Output */
	SWM_CLKOUT_O        = 0x82,	/*!< PINASSIGN8 - I2C CLKOUT Output */
	SWM_GPIO_INT_BMAT_O = 0x83,	/*!< PINASSIGN8 - I2C GPIO INT BMAT Output */
} CHIP_SWM_PIN_MOVABLE_T;

/**
 * @brief LPC8XX Switch Matrix Fixed pins
 */
typedef enum CHIP_SWM_PIN_FIXED    {
	ACMP_I1 = 0,	/*!< ACMP I1 */
	ACMP_I2 = 1,	/*!< ACMP I2 */
	SWCLK = 2,		/*!< SWCLK */
	SWDIO  = 3,		/*!< SWDIO */
	XTALIN = 4,		/*!< XTALIN */
	XTALOUT = 5,	/*!< XTALOUT */
	RST     = 6,	/*!< Reset */
	CLKIN = 7,		/*!< Clock Input */
	VDDCMP = 8		/*!< VDD */
} CHIP_SWM_PIN_FIXED_T;

/**
 * @brief	Initialise the SWM module
 * @return	Nothing
 */
STATIC INLINE void Chip_SWM_Init(void)
{
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SWM);
}

/**
 * @brief	Deinitialise the SWM module
 * @return	Nothing
 */
STATIC INLINE void Chip_SWM_Deinit(void)
{
	Chip_Clock_DisablePeriphClock(SYSCTL_CLOCK_SWM);
}

/**
 * @brief	Assign movable pin function to physical pin in Switch Matrix
 * @param	movable	: Movable pin function
 * @param	assign	: Physical pin to be assigned
 * @return	Nothing
 */
void Chip_SWM_MovablePinAssign(CHIP_SWM_PIN_MOVABLE_T movable, CHIP_PINx_T assign);

/**
 * @brief	Enables or Disable Fixed Function Pin in the Switch Matrix
 * @param	pin		: Pin to be enabled or disabled
 * @param	enable	: True to enable the pin, False to disable the pin
 * @return	Nothing
 */
void Chip_SWM_FixedPinEnable(CHIP_SWM_PIN_FIXED_T pin, bool enable);

/**
 * @brief	Tests whether a pin is enabled or disabled in the Switch Matrix
 * @param	pin		: The pin to test whether it is enabled or disabled
 * @return	True if the pin is enabled, False if disabled
 */
bool Chip_SWM_IsEnabled(CHIP_SWM_PIN_FIXED_T pin);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __SWM_8XX_H_ */
