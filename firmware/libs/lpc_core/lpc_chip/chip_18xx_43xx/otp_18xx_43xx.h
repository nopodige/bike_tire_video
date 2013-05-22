/*
 * @brief LPC18xx/43xx OTP Controller driver
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

#ifndef __OTP_18XX_43XX_H_
#define __OTP_18XX_43XX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup OTP_18XX_43XX CHIP: LPC18xx/43xx OTP Controller driver
 * @ingroup CHIP_18XX_43XX_Drivers
 * @{
 */

/**
 * @brief	OTP Register block
 */
typedef struct {
	__IO uint32_t OTP0_0;				/*!< (@ 0x40045000) OTP content */
	__IO uint32_t OTP0_1;				/*!< (@ 0x40045004) OTP content */
	__IO uint32_t OTP0_2;				/*!< (@ 0x40045008) OTP content */
	__IO uint32_t OTP0_3;				/*!< (@ 0x4004500C) OTP content */
	__IO uint32_t OTP1_0;				/*!< (@ 0x40045010) OTP content */
	__IO uint32_t OTP1_1;				/*!< (@ 0x40045014) OTP content */
	__IO uint32_t OTP1_2;				/*!< (@ 0x40045018) OTP content */
	__IO uint32_t OTP1_3;				/*!< (@ 0x4004501C) OTP content */
	__IO uint32_t OTP2_0;				/*!< (@ 0x40045020) OTP content */
	__IO uint32_t OTP2_1;				/*!< (@ 0x40045024) OTP content */
	__IO uint32_t OTP2_2;				/*!< (@ 0x40045028) OTP content */
	__IO uint32_t OTP2_3;				/*!< (@ 0x4004502C) OTP content */
	uint32_t RESERVED0[4];
	__IO uint32_t UNIQUE_KEY0;			/*!< (@ 0x40045040) Unique Key bit 31..0. R/W locked at default */
	__IO uint32_t UNIQUE_KEY1;			/*!< (@ 0x40045044) Unique Key bit 63..32. R/W locked at default */
	__IO uint32_t UNIQUE_KEY2;			/*!< (@ 0x40045048) Unique Key bit 95..64. R/W locked at default */
	__IO uint32_t UNIQUE_KEY3;			/*!< (@ 0x4004504C) Unique Key bit 127..96. R/W locked at default */
	__IO uint32_t RANDOM_NUM0;			/*!< (@ 0x40045050) Random number bit 31..0. R/W locked at default */
	__IO uint32_t RANDOM_NUM1;			/*!< (@ 0x40045054) Random number bit 63..32. R/W locked at default */
	__IO uint32_t RANDOM_NUM2;			/*!< (@ 0x40045058) Random number bit 95..64. R/W locked at default */
	__IO uint32_t RANDOM_NUM3;			/*!< (@ 0x4004505C) Random number bit 127..96. R/W locked at default */
	__IO uint32_t USER_KEY0;			/*!< (@ 0x40045060) User Key bit 31..0. R locked at default */
	__IO uint32_t USER_KEY1;			/*!< (@ 0x40045064) User Key bit 63..32. R locked at default */
	__IO uint32_t USER_KEY2;			/*!< (@ 0x40045068) User Key bit 95..64. R locked at default */
	__IO uint32_t USER_KEY3;			/*!< (@ 0x4004506C) User Key bit 127..96. R locked at default */
	uint32_t RESERVED1[4];
	__IO uint32_t WRTMASK;				/*!< (@ 0x40045080) Masks APB write to fuses */
	__O  uint32_t STATUS;				/*!< (@ 0x40045084) Indicates write status of fuses */
	uint32_t RESERVED2[2];
	__IO uint32_t PROGRAM;				/*!< (@ 0x40045090) Enables write of Shuffled AES value to OTP1c */
	__IO uint32_t AES_SSEL;				/*!< (@ 0x40045094) Controls selecting source for SKey output to AES Engine */
	__IO uint32_t SHUFFLE_CTRL;			/*!< (@ 0x40045098) Shuffle block control */
	uint32_t RESERVED3;
	__IO uint32_t OTP0_WR_LOCK;			/*!< (@ 0x400450A0) Locks write access to itself and OTP0 write access */
	__IO uint32_t OTP0_RD_LOCK;			/*!< (@ 0x400450A4) Locks write access to itself and OTP0 read access */
	__IO uint32_t OTP1_WR_LOCK;			/*!< (@ 0x400450A8) Locks write access to itself and OTP1 write access */
	__IO uint32_t OTP1_RD_LOCK;			/*!< (@ 0x400450AC) Locks write access to itself and OTP1 read access */
	__IO uint32_t OTP2_WR_LOCK;			/*!< (@ 0x400450B0) Locks write access to itself and OTP2 write access */
	__IO uint32_t OTP2_RD_LOCK;			/*!< (@ 0x400450B4) Locks write access to itself and OTP2 read access */
	__IO uint32_t RESERVED4[2];
	__IO uint32_t UNIQUE_KEY_WR_LOCK;	/*!< (@ 0x400450C0) Locks write access to itself and Unique Key write access */
	__IO uint32_t UNIQUE_KEY_RD_LOCK;	/*!< (@ 0x400450C4)  */
	__IO uint32_t RANDOM_NUM_WR_LOCK;	/*!< (@ 0x400450C8)  */
	__IO uint32_t RANDOM_NUM_RD_LOCK;	/*!< (@ 0x400450CC)  */
	__IO uint32_t RESERVED5;				/*!< (@ 0x400450D0)  */
	__IO uint32_t USER_KEY_RD_LOCK;		/*!< (@ 0x400450D4)  */
} LPC_OTP_T;

/**
 * @brief	OTP Boot Source selection used in Chip driver
 */
typedef enum CHIP_OTP_BOOT_SRC {
	CHIP_OTP_BOOTSRC_PINS,		/*!< Boot source - External pins */
	CHIP_OTP_BOOTSRC_UART0,		/*!< Boot source - UART0 */
	CHIP_OTP_BOOTSRC_SPIFI,		/*!< Boot source - EMC 8-bit memory */
	CHIP_OTP_BOOTSRC_EMC8,		/*!< Boot source - EMC 16-bit memory */
	CHIP_OTP_BOOTSRC_EMC16,		/*!< Boot source - EMC 32-bit memory */
	CHIP_OTP_BOOTSRC_EMC32,		/*!< Boot source - EMC 32-bit memory */
	CHIP_OTP_BOOTSRC_USB0,		/*!< Boot source - DFU USB0 boot */
	CHIP_OTP_BOOTSRC_USB1,		/*!< Boot source - DFU USB1 boot */
	CHIP_OTP_BOOTSRC_SPI,		/*!< Boot source - SPI boot */
	CHIP_OTP_BOOTSRC_UART3		/*!< Boot source - UART3 */
} CHIP_OTP_BOOT_SRC_T;

/**
 * @brief	Initialize for OTP Controller functions
 * @return	 Status of Otp_Init function
 * This function will initialise all the OTP driver function pointers
 * and call the ROM OTP Initialisation function.
 */
uint32_t Chip_OTP_Init(void);

/**
 * @brief	Program boot source in OTP Controller
 * @param	BootSrc	: Boot Source enum value
 * @return	Status
 */
uint32_t Chip_OTP_ProgBootSrc(CHIP_OTP_BOOT_SRC_T BootSrc);

/**
 * @brief	Program the JTAG bit in OTP Controller
 * @return	Status
 */
uint32_t Chip_OTP_ProgJTAGDis(void);

/**
 * @brief	Program USB ID in OTP Controller
 * @param	ProductID	: USB Product ID
 * @param	VendorID	: USB Vendor ID
 * @return	Status
 */
uint32_t Chip_OTP_ProgUSBID(uint32_t ProductID, uint32_t VendorID);

/**
 * @brief	Program OTP GP Word memory
 * @param   WordNum     : Word Number (Select word 0 or word 1 or word 2)
 * @param	Data	    : Data value
 * @param	Mask        : Mask value
 * @return	Status
 * This function available in devices which are not AES capable
 */
uint32_t Chip_OTP_ProgGPWord(uint32_t WordNum, uint32_t Data, uint32_t Mask);

/**
 * @brief	Program AES Key
 * @param   KeyNum      : Key Number (Select 0 or 1)
 * @param	key         : Pointer to AES Key (16 bytes required)
 * @return	Status
 * This function available in devices which are AES capable
 */
uint32_t Chip_OTP_ProgKey(uint32_t KeyNum, uint8_t *key);

/**
 * @brief	Generate Random Number using HW Random Number Generator
 * @return	Random Number value
 */
uint32_t Chip_OTP_GenRand(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __OTP_18XX_43XX_H_ */
