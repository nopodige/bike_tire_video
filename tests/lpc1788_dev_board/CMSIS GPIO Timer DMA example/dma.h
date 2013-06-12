/***********************************************************************
*
* Project: LPC17XX DMA controller definitions
*
* Description:
*     This file contains the structure definitions and manifest
*     constants for the LPC17XX chip family component:
*         DMA controller
*
***********************************************************************
* Software that is described herein is for illustrative purposes only  
* which provides customers with programming information regarding the  
* products. This software is supplied "AS IS" without any warranties.  
* NXP Semiconductors assumes no responsibility or liability for the 
* use of the software, conveys no license or title under any patent, 
* copyright, or mask work right to the product. NXP Semiconductors 
* reserves the right to make changes in the software without 
* notification. NXP Semiconductors also make no representation or 
* warranty that such application will be suitable for the specified 
* use without further testing or modification. 
**********************************************************************/

#ifndef DMAC_H
#define DMAC_H

#include <LPC17xx.h>
#include "type.h"

#ifdef __cplusplus
extern "C" {
#endif


/**********************************************************************
* DMA controller register structures
**********************************************************************/

/* DMA controller channel register structure */
typedef struct {
    volatile uint32_t src_addr;           /* Source address reg */
    volatile uint32_t dest_addr;          /* Destination address reg */
    volatile uint32_t lli;                /* Linked list item reg */
    volatile uint32_t control;            /* Channel control reg */
    volatile uint32_t config_ch;          /* Channel config reg */
    volatile uint32_t reserved [3];
} DMAC_CHAN_T;

/* DMA controller register structures */ 
typedef struct {
    volatile uint32_t int_stat;           /* Interrupt int32_t reg */
    volatile uint32_t int_tc_stat;        /* INT terminal count req sts */
    volatile uint32_t int_tc_clear;       /* INT terminal count clear */
    volatile uint32_t int_err_stat;       /* Interrupt error sts reg */
    volatile uint32_t int_err_clear;      /* Interrupt error clear reg */
    volatile uint32_t raw_tc_stat;        /* Raw terminal count reg */
    volatile uint32_t raw_err_stat;       /* Raw error int32_t reg */
    volatile uint32_t chan_enable;        /* Enabled channel reg */
    volatile uint32_t sw_burst_req;       /* SW burst req reg */
    volatile uint32_t sw_single_req;      /* SW single req reg */
    volatile uint32_t sw_last_burst_req;  /* SW last burst req reg */
    volatile uint32_t sw_last_single_req; /* SW last single req reg */
    volatile uint32_t config;             /* Config register */
    volatile uint32_t sync;               /* Synchronization register */
    volatile uint32_t reserved [50];
    DMAC_CHAN_T     dma_chan [8];       /* Individual DMA chan regs */
} DMAC_REGS_T;

/* DMA linked list structure used with a channel's LLI register */
typedef struct 
{
	volatile uint32_t dma_src;     /* Source for data transfer */
	volatile uint32_t dma_dest;    /* Destination for data transfer */
	volatile uint32_t next_lli;    /* Next linked list pointer or NULL */
	volatile uint32_t next_ctrl;   /* DMA control word for list entry */
} DMAC_LL_T;

/**********************************************************************
* int_stat, int_tc_stat, int_tc_clear, int_err_stat, raw_tc_stat,
* raw_err_stat, and chan_enable register definitions
**********************************************************************/
/* Macro for determining a bit position for a channel */
#define DMAC_GET_CHAN_POS(chan)     (0x1 << ((chan) & 0x7))

/**********************************************************************
* sw_burst_req, sw_single_req, sw_last_burst_req, sw_last_single_req,
* and sync register definitions
**********************************************************************/
/* Peripheral DMA bit position for I2S0 DMA0 */
#define DMA_PER_I2S0_DMA0           _BIT(0)

/* Peripheral DMA bit position for NAND FLASH (same as 12) */
#define DMA_PER_NAND1               _BIT(1)

/* Peripheral DMA bit position for I2S1 DMA0 */
#define DMA_PER_I2S1_DMA0           _BIT(2)

/* Peripheral DMA bit position for SPI2 (RX and TX) */
#define DMA_PER_SPI2_TXRX           _BIT(3)

/* Peripheral DMA bit position for SSP1 (RX) */
#define DMA_PER_SSP1_RX             _BIT(3)

/* Peripheral DMA bit position for SD card */
#define DMA_PER_SDCARD              _BIT(4)

/* Peripheral DMA bit position for HSUART1 TX */
#define DMA_PER_HSUART1_TX          _BIT(5)

/* Peripheral DMA bit position for HSUART1 RX */
#define DMA_PER_HSUART1_RX          _BIT(6)

/* Peripheral DMA bit position for HSUART2 TX */
#define DMA_PER_HSUART2_TX          _BIT(7)

/* Peripheral DMA bit position for HSUART2 RX */
#define DMA_PER_HSUART2_RX          _BIT(8)

/* Peripheral DMA bit position for HSUART7 TX */
#define DMA_PER_HSUART7_TX          _BIT(9)

/* Peripheral DMA bit position for HSUART7 RX */
#define DMA_PER_HSUART7_RX          _BIT(10)

/* Peripheral DMA bit position for I2S1 DMA1 */
#define DMA_PER_I2S1_DMA1           _BIT(10)

/* Peripheral DMA bit position for SPI1 (RX and TX) */
#define DMA_PER_SPI1_TXRX           _BIT(11)

/* Peripheral DMA bit position for SSP1 (TX) */
#define DMA_PER_SSP1_TX             _BIT(11)

/* Peripheral DMA bit position for NAND FLASH (same as 1) */
#define DMA_PER_NAND2               _BIT(12)

/* Peripheral DMA bit position for I2S0 DMA1 */
#define DMA_PER_I2S0_DMA1           _BIT(13)

/* Peripheral DMA bit position for SSP0 (RX) */
#define DMA_PER_SSP0_RX             _BIT(14)

/* Peripheral DMA bit position for SSP0 (TX) */
#define DMA_PER_SSP0_TX             _BIT(15)

/**********************************************************************
* config register definitions
**********************************************************************/
/* Bit for enabling big endian mode on AHB 1 */
#define DMAC_BIG_ENDIAN_AHB1        _BIT(2)

/* Bit for enabling big endian mode on AHB 0 */
#define DMAC_BIG_ENDIAN_AHB0        _BIT(1)

/* Bit for enabling the DMA controller */
#define DMAC_CTRL_ENABLE            _BIT(0)

/**********************************************************************
* lli register definitions
**********************************************************************/
/* Bit for selecting AHB0 (0) or AHB1 (1) */
#define DMAC_CHAN_LLI_SEL_AHB1      _BIT(0)

/**********************************************************************
* control register definitions
**********************************************************************/
/* Bit for enabling a channel terminal count interrupt */
#define DMAC_CHAN_INT_TC_EN         _BIT(31)

/* Bit for indicating address is cacheable */
#define DMAC_CHAN_PROT3             _BIT(30)

/* Bit for indicating address is bufferable */
#define DMAC_CHAN_PROT2             _BIT(29)

/* Bit for indicating address is privelaged mode (1) or user
   mode (0) */
#define DMAC_CHAN_PROT1             _BIT(28)

/* Bit for enabling automatic destination increment */
#define DMAC_CHAN_DEST_AUTOINC      _BIT(27)

/* Bit for enabling automatic source increment */
#define DMAC_CHAN_SRC_AUTOINC       _BIT(26)

/* Destination data width selection defines */
#define DMAC_CHAN_DEST_WIDTH_8      0x0
#define DMAC_CHAN_DEST_WIDTH_16     _BIT(21)
#define DMAC_CHAN_DEST_WIDTH_32     _BIT(22)

/* Source data width selection defines */
#define DMAC_CHAN_SRC_WIDTH_8       0x0
#define DMAC_CHAN_SRC_WIDTH_16      _BIT(18)
#define DMAC_CHAN_SRC_WIDTH_32      _BIT(19)

/* Destination data burst size defines (in transfer width) */
#define DMAC_CHAN_DEST_BURST_1      0
#define DMAC_CHAN_DEST_BURST_4      _BIT(15)
#define DMAC_CHAN_DEST_BURST_8      _BIT(16)
#define DMAC_CHAN_DEST_BURST_16     (_BIT(16) | _BIT(15))
#define DMAC_CHAN_DEST_BURST_32     _BIT(17)
#define DMAC_CHAN_DEST_BURST_64     (_BIT(17) | _BIT(15))
#define DMAC_CHAN_DEST_BURST_128    (_BIT(17) | _BIT(16))
#define DMAC_CHAN_DEST_BURST_256    (_BIT(17) | _BIT(16) | _BIT(15))

/* Macro for direct loading of destination burst size field */
#define DMAC_CHAN_DEST_BURST_LOAD(n) (((n) & 0x7) << 15)

/* Source data burst size defines (in transfer width) */
#define DMAC_CHAN_SRC_BURST_1       0
#define DMAC_CHAN_SRC_BURST_4       _BIT(12)
#define DMAC_CHAN_SRC_BURST_8       _BIT(13)
#define DMAC_CHAN_SRC_BURST_16      (_BIT(13) | _BIT(12))
#define DMAC_CHAN_SRC_BURST_32      _BIT(14)
#define DMAC_CHAN_SRC_BURST_64      (_BIT(14) | _BIT(12))
#define DMAC_CHAN_SRC_BURST_128     (_BIT(14) | _BIT(13))
#define DMAC_CHAN_SRC_BURST_256     (_BIT(14) | _BIT(13) | _BIT(12))

/* Macro for direct loading of source burst size field */
#define DMAC_CHAN_SRC_BURST_LOAD(n) (((n) & 0x7) << 12)

/* Macro for loading transfer size */
#define DMAC_CHAN_TRANSFER_SIZE(n)  ((n) & 0xFFF)

/**********************************************************************
* config_ch register definitions
**********************************************************************/
/* Bit for halting a DMA transfer */
#define DMAC_CHAN_HALT              _BIT(18)

/* Bit for checking active int32_t of the DMA channel */
#define DMAC_CHAN_ACTIVE            _BIT(17)

/* Bit for enabling locked transfers */
#define DMAC_CHAN_LOCK              _BIT(16)

/* Terminal count interrupt mask bit */
#define DMAC_CHAN_ITC               _BIT(15)

/* Interrupt error mask bit */
#define DMAC_CHAN_IE                _BIT(14)

/* Defines for flow control with DMA as the controller */
#define DMAC_CHAN_FLOW_D_M2M        (0x0 << 11)
#define DMAC_CHAN_FLOW_D_M2P        (0x1 << 11)
#define DMAC_CHAN_FLOW_D_P2M        (0x2 << 11)
#define DMAC_CHAN_FLOW_D_SP2DP      (0x3 << 11)

/* Defines for flow control with destination peripheral as the
   controller */
#define DMAC_CHAN_FLOW_DP_SP2DP     (0x4 << 11)

/* Defines for flow control with peripheral as the controller */
#define DMAC_CHAN_FLOW_P_M2P        (0x5 << 11)
#define DMAC_CHAN_FLOW_P_P2M        (0x6 << 11)

/* Defines for flow control with source peripheral as the
   controller */
#define DMAC_CHAN_FLOW_SP_SP2DP     (0x7 << 11)

/* Macro for loading destination peripheral */
#define DMAC_DEST_PERIP(n)          (((n) & 0x1F) << 6)

/* Macro for loading source peripheral */
#define DMAC_SRC_PERIP(n)           (((n) & 0x1F) << 1)

/* Channel enable bit */
#define DMAC_CHAN_ENABLE            _BIT(0)

/**********************************************************************
* config_ch register definitions (source and destination
* peripheral ID numbers). These can be used with the DMAC_DEST_PERIP
* and DMAC_SRC_PERIP macros.
**********************************************************************/
#define DMA_PERID_I2S0_DMA0         0
#define DMA_PERID_NAND1             1
#define DMA_PERID_I2S1_DMA0         2
#define DMA_PERID_SPI2_TXRX         3
#define DMA_PERID_SSP1_RX           3
#define DMA_PERID_SDCARD            4
#define DMA_PERID_HSUART1_TX        5
#define DMA_PERID_HSUART1_RX        6
#define DMA_PERID_HSUART2_TX        7
#define DMA_PERID_HSUART2_RX        8
#define DMA_PERID_HSUART7_TX        9
#define DMA_PERID_HSUART7_RX        10
#define DMA_PERID_I2S1_DMA1         10
#define DMA_PERID_SPI1_TXRX         11
#define DMA_PERID_SSP1_TX           11
#define DMA_PERID_NAND2             12
#define DMA_PERID_I2S0_DMA1         13
#define DMA_PERID_SSP0_RX           14
#define DMA_PERID_SSP0_TX           15

/* Macro pointing to DMA registers */
#define DMAC ((DMAC_REGS_T *)(0x50004000))


/***********************************************************************
 * DMA driver functions
 **********************************************************************/

/* Initial DMA controller and driver */
int32_t dma_init(void);

/* Allocate a channel for DMA, use ch for selected channel (0 to 7) or
   -1 to use the highest priority available channel. Also sets up the
   user callback function for the channel's DMA interrupt. */
int32_t dma_alloc_channel(int32_t ch,
                         PFV cb);

/* Return (free) an allocated DMA channel */
int32_t dma_free_channel(int32_t ch);

/* Start a M2M transfer on an allocated DMA channel */
int32_t dma_start_m2m(int32_t ch,
                     void *src,
                     void *dest,
                     DMAC_LL_T *plli,
                     int32_t trans);

/* Start a M2PIN transfer on an allocated DMA channel */
int32_t dma_start_m2pin(int32_t ch,
                     void *src,
                     void *dest,
                     DMAC_LL_T *plli,
                     int32_t trans);

/* Make a linked list entry (for virtual addresses only) */
void dma_setup_virt_link(DMAC_LL_T *plink,
                         uint32_t *dmasrc_virt,
                         uint32_t *dmadest_virt,
                         uint32_t dma_ctrl);

/* Make a linked list entry (for physical addresses only) */
void dma_setup_link_phy(DMAC_LL_T *plink,
                        uint32_t *dmasrc_phy,
                        uint32_t *dmadest_phy,
                        uint32_t dma_ctrl);

/* Enable or disable SYNC logic for a specific peripheral, periph must
   be a value of type DMA_PER_xxx, see the DMA peripheral header file */
void dma_enable_sync(uint32_t periph,
                     uint32_t enable);

/* Return pointer to DMA registers */
DMAC_REGS_T *dma_get_base(void);


#ifdef __cplusplus
}
#endif

#endif 
