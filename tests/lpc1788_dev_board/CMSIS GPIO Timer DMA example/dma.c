/*****************************************************************************
 *   gpdma.c:  GPDMA module file for NXP LPC17xx Family Microprocessors
 *
 *   Copyright(C) 2008, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2008.09.18  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include <LPC17xx.h>
#include "type.h"
#include "target.h"
#include "it.h"
#include "dma.h"

extern volatile PFV cb [MAX_IRQChannel];
void vic_enable_ch(uint32_t channel, uint32_t option);

#define PCGPDMA     (1<<29)

/***********************************************************************
 * DMA driver private data
***********************************************************************/

/* Number of DMA channels */
#define DMA_MAX_CHANNELS 8

/* DMA driver control structure */
typedef struct 
{
	int32_t init;
	int32_t  alloc_ch [DMA_MAX_CHANNELS];
	PFV     cb [DMA_MAX_CHANNELS];
	int32_t  num_alloc_ch;    /* Number of allocated channels */
	DMAC_REGS_T *pdma;
} DMA_DRV_DATA_T;

/* DMAS driver data */
static DMA_DRV_DATA_T dmadrv_dat;


/***********************************************************************
 * DMA driver private functions
***********************************************************************/
/*
void vic_enable_ch(uint32_t channel, uint32_t option)
{
    channel = channel & 0x7F;
    switch ((channel & 0x60)>>5)
    {
        case 0: if (option == 0)
                    NVIC_DISABLE0 = 1<<(channel & 0x1F);
                else
                    NVIC_ENABLE0 |= 1<<(channel & 0x1F);
                break;
        case 1: if (option == 0)
                    NVIC_DISABLE1 = 1<<(channel & 0x1F);
                else
                    NVIC_ENABLE1 |= 1<<(channel & 0x1F);
                break;
        case 2: if (option == 0)
                    NVIC_DISABLE2 = 1<<(channel & 0x1F);
                else
                    NVIC_ENABLE2 |= 1<<(channel & 0x1F);
                break;
        case 3: if (option == 0)
                    NVIC_DISABLE3 = 1<<(channel & 0x1F);
                else
                    NVIC_ENABLE3 |= 1<<(channel & 0x1F);
                break;
        default:
                break;
    }
    return;
}
*/
/***********************************************************************
 *
 * Function: dma_interrupt
 *
 * Purpose: DMA controller interrupt handler
 *
 * Processing:
 *     This function is called when a DMA interrupt occurs. It looks at
 *     the DMA int32_tes and calls the user defined callback function
 *     for the active DMA channel if it exists. If a callback function
 *     doesn't exist, then interrupt support for the DMA channel is
 *     disabled.
 * 
 * Parameters: None
 *
 * Outputs: None
 *
 * Returns: Nothing
 *
 * Notes: None
 *
 **********************************************************************/
//void DMA_Handler(void)
//{
//	int32_t ch;
//	uint32_t sts_int;
//
//	/* Get DMA int32_tes */
//	sts_int = dmadrv_dat.pdma->int_stat;
//
//	/* Check all pending interrupt int32_tes */
//	ch = 0;
//	while (ch < DMA_MAX_CHANNELS)
//	{
//		/* Check channel interrupt int32_t */
//		if ((sts_int & _BIT(ch)) != 0)
//		{
//			/* Channel interrupt is pending */
//			if (dmadrv_dat.cb [ch] != NULL)
//			{
//				/* Call user defined callback function */
//				dmadrv_dat.cb [ch]();
//			}
//			else
//			{
//				/* Interrupt is pending, but no user callback function
//				   exists, so disable the interrupts for this channel
//				   to prevent the interrupt from continuously firing */
//				dmadrv_dat.pdma->dma_chan [ch].control &=
//					~DMAC_CHAN_INT_TC_EN;
//				dmadrv_dat.pdma->dma_chan [ch].config_ch &=
//					~(DMAC_CHAN_ITC | DMAC_CHAN_IE);
//			}
//		}
//
//		/* Next channel */
//		ch++;
//	}
//}

/***********************************************************************
 * DMA driver public functions
***********************************************************************/

/***********************************************************************
 *
 * Function: dma_init
 *
 * Purpose: Initial DMA controller and driver
 *
 * Processing:
 *     This function sets up the DMA controller as initially disabled.
 *     All DMA channels used by the driver are unallocated.
 * 
 * Parameters: None
 *
 * Outputs: None
 *
 * Returns:
 *     _ERROR if the device was already initialized, otherside _NO_ERROR
 *
 * Notes: None
 *
 **********************************************************************/
int32_t dma_init(void)
{
	int32_t idx;
	int32_t init = _ERROR;

	/* Only continue if driver has not been previously initialized */
	if (dmadrv_dat.init == FALSE)
	{
		dmadrv_dat.init = TRUE;
		dmadrv_dat.num_alloc_ch = 0;

		/* Save base address of DMA controller registers */
		//dmadrv_dat.pdma = (DMAC_REGS_T *) DMA_BASE_ADDR;
		dmadrv_dat.pdma = (DMAC_REGS_T *) GPDMA;

		/* Enable clock to DMA controller (for now) */
        SC->PCONP |= PCGPDMA;

		/* Make sure DMA controller and all channels are disabled.
		   Controller is in little-endian mode. Disable sync signals */
		dmadrv_dat.pdma->config = 0;
		dmadrv_dat.pdma->sync = 0;

		/* Clear interrupt and error int32_tes */
		dmadrv_dat.pdma->int_tc_clear = 0xFF;
		dmadrv_dat.pdma->raw_tc_stat = 0xFF;

		/* All DMA channels are initially disabled and unallocated */
		for (idx = 0; idx < DMA_MAX_CHANNELS; idx++)
		{
			/* Channel is currently unallocated */
			dmadrv_dat.alloc_ch [idx] = FALSE;
			dmadrv_dat.cb [idx] = NULL;

			/* Make sure channel is disabled */
			dmadrv_dat.pdma->dma_chan [idx].control = 0;
			dmadrv_dat.pdma->dma_chan [idx].config_ch = 0;
		}

		/* Disable clock to DMA controller. The clock will only be
		   enabled when one or moer channels are active. */
		SC->PCONP &= ~PCGPDMA;

		init = _NO_ERROR;
	}

	return init;
}

/***********************************************************************
 *
 * Function: dma_alloc_channel
 *
 * Purpose: Allocate a channel for DMA
 *
 * Processing:
 *     If the passed channel is (-1), then a search loop is used to
 *     find the first unallocated channel. The channel value is saved
 *     and then checked to make sure it is unallocated. If it is
 *     already allocated or not allocatable, then an error si return to
 *     the caller. If the channel is not allocated, the channel is
 *     marked as allocated and the channel ID is returned to the caller.
 *     If at leasxt one channel is active, the DMA clock is enabled.
 * 
 * Parameters:
 *     ch : Must be 0 (highest priority) to 7, or -1 for auto-allocation
 *     cb : Pointer to user callback function when an interrupt occurs
 *
 * Outputs: None
 *
 * Returns: The channel index, or _ERROR if a channel wasn't allocated
 *
 * Notes: None
 *
 **********************************************************************/
int32_t dma_alloc_channel(int32_t ch,
                         PFV cbk)
{
	int32_t challoc = ch;

	/* If auto-allocate is used, find the first available channel
	   starting with the highest priority first */
	if (ch == -1)
	{
		ch = 0;
		challoc = _ERROR;
		while (ch < DMA_MAX_CHANNELS)
		{
			if (dmadrv_dat.alloc_ch [ch] == FALSE)
			{
				/* Channel is free, use it */
				challoc = ch;
				ch = DMA_MAX_CHANNELS;
			}
			else 
			{
				/* Try next channel */
				ch++;
			}
		}
	}

	/* Only continue if channel is ok */
	if (challoc != _ERROR)
	{
		/* If the current channel is allocated already, then return an
 		   error instead */
		if (dmadrv_dat.alloc_ch [challoc] == FALSE)
		{
			/* Channel is free, so use it */
			dmadrv_dat.alloc_ch [challoc] = TRUE;
			dmadrv_dat.cb [challoc] = cbk;
			dmadrv_dat.num_alloc_ch++;

			/* Enable DMA clock if at least 1 DMA channel is used */
			if (dmadrv_dat.num_alloc_ch == 1)
			{
				SC->PCONP |= PCGPDMA;
			   
				/* Enable DMA controller */
				dmadrv_dat.pdma->config = DMAC_CTRL_ENABLE;

				/* Install DMA interrupt handler in interrupt controller
				   and enable DMA interrupt */
//				cb[DMA_IRQChannel] = (PFV)DMA_Handler; 
//                vic_enable_ch(DMA_IRQChannel,1);
	    	}
		}
		else 
		{
			/* Selected channel is allocated, return an error */
			challoc = _ERROR;
		}
	}

	return challoc;
}

/***********************************************************************
 *
 * Function: dma_free_channel
 *
 * Purpose: Return (free) an allocated DMA channel
 *
 * Processing:
 *     If the channel has been previously allocated, then deallocate
 *     the channel and disable the channel in the DMA controller. If
 *     no other DMA channels are enabled, the disable the DMA controller
 *     along with the controller clock and DMA interrupts.
 * 
 * Parameters:
 *     ch : Must be 0 to 7
 *
 * Outputs: None
 *
 * Returns: _NO_ERROR if the channel was freed, otherwise _ERROR
 *
 * Notes: None
 *
 **********************************************************************/
int32_t dma_free_channel(int32_t ch)
{
	int32_t status = _ERROR;
	if (dmadrv_dat.alloc_ch [ch] == TRUE)
	{
		/* Deallocate channel */
		dmadrv_dat.alloc_ch [ch] = FALSE;
		dmadrv_dat.num_alloc_ch--;

		/* Shut down channel */
		dmadrv_dat.pdma->dma_chan [ch].control = 0;
		dmadrv_dat.pdma->dma_chan [ch].config_ch = 0;
		dmadrv_dat.pdma->sync &= ~_BIT(ch);

		/* If no other DMA channels are enabled, then disable the DMA
		   controller and disable the DMA clock */
		if (dmadrv_dat.num_alloc_ch == 0)
		{
			dmadrv_dat.pdma->config = 0;
			SC->PCONP &= ~PCGPDMA;

			/* Disable DMA interrupt */
//			cb[DMA_IRQChannel] = (PFV)DMA_Handler; 
//			cb[DMA_IRQChannel] = (PFV)NULL; 
//            vic_enable_ch(DMA_IRQChannel,0);
		}

		status = _NO_ERROR;
	}

	return status;
}

/***********************************************************************
 *
 * Function: dma_start_m2m
 *
 * Purpose: Start a M2M transfer on an allocated DMA channel
 *
 * Processing:
 *     A default memmory to memory DMA operation is performed with the
 *     passed channel, source, destination, and size. If the linked
 *     list pointer is not NULL, the DMA transfer is setup from the
 *     first linked list entry (including the control word).
 * 
 * Parameters:
 *     ch    : Must be 0 to 7
 *     src   : Physical address of source data
 *     dest  : Physical address of destination data
 *     plli  : Physcial address of linked list (negates src and dest)
 *     trans : Number of transfers (when plli is NULL)
 *
 * Outputs: None
 *
 * Returns: _NO_ERROR if the transfer was started, otherwise _ERROR
 *
 * Notes:
 *     This is a basic memory to memory transfer function. This starts
 *     the transfer and returns immediately before the transfer may be
 *     complete. No int32_t about the ongoing transfer is returned to
 *     the caller. If more control or int32_t is needed by the caller,
 *     it should monitor and check DMA channel int32_t after the call to
 *     this function, or use an alternate function.
 *
 **********************************************************************/
int32_t dma_start_m2m(int32_t ch,
                     void *src,
                     void *dest,
                     DMAC_LL_T *plli,
                     int32_t trans)
{
	int32_t sts = _ERROR;

	/* Verify that the selected channel has been allocated */
	if (dmadrv_dat.alloc_ch [ch] == TRUE)
	{
		/* Setup source and destination and clear LLI */
		dmadrv_dat.pdma->dma_chan [ch].src_addr = (uint32_t) src;
		dmadrv_dat.pdma->dma_chan [ch].dest_addr = (uint32_t) dest;
		dmadrv_dat.pdma->dma_chan [ch].lli = (uint32_t) plli;

		/* Use linked list control word if available */
		if (plli != NULL)
		{
			dmadrv_dat.pdma->dma_chan [ch].control = plli->next_ctrl;
		}
		else 
		{
			/* Setup channel configuration */
			dmadrv_dat.pdma->dma_chan [ch].control =
			    (DMAC_CHAN_INT_TC_EN | DMAC_CHAN_DEST_AUTOINC |
		    	DMAC_CHAN_SRC_AUTOINC | DMAC_CHAN_DEST_WIDTH_8 |
			    DMAC_CHAN_SRC_WIDTH_8 | DMAC_CHAN_DEST_BURST_1 |
			    DMAC_CHAN_SRC_BURST_1 |
			    DMAC_CHAN_TRANSFER_SIZE(trans));
		}

		/* Start channel transfer */
		dmadrv_dat.pdma->dma_chan [ch].config_ch =
			(DMAC_CHAN_FLOW_D_P2M | DMAC_CHAN_ENABLE | DMAC_SRC_PERIP(9) );
	
		sts = _NO_ERROR;
	}

	return sts;
}


/* extensions for test DMA to FIOPIN */
int32_t dma_start_m2pin(int32_t ch,
                     void *src,
                     void *dest,
                     DMAC_LL_T *plli,
                     int32_t trans)
{
	int32_t sts = _ERROR;

	/* Verify that the selected channel has been allocated */
	if (dmadrv_dat.alloc_ch [ch] == TRUE)
	{
		/* Setup source and destination and clear LLI */
		dmadrv_dat.pdma->dma_chan [ch].src_addr = (uint32_t) src;
		dmadrv_dat.pdma->dma_chan [ch].dest_addr = (uint32_t) dest;
		dmadrv_dat.pdma->dma_chan [ch].lli = (uint32_t) plli;

		/* Use linked list control word if available */
		if (plli != NULL)
		{
			dmadrv_dat.pdma->dma_chan [ch].control = plli->next_ctrl;
		}
		else 
		{
			/* Setup channel configuration */
			dmadrv_dat.pdma->dma_chan [ch].control =
			    (DMAC_CHAN_INT_TC_EN | 	
		    	DMAC_CHAN_SRC_AUTOINC | DMAC_CHAN_DEST_WIDTH_8 |
			    DMAC_CHAN_SRC_WIDTH_8 | DMAC_CHAN_DEST_BURST_1 |
			    DMAC_CHAN_SRC_BURST_1 |
			    DMAC_CHAN_TRANSFER_SIZE(trans));
		}

		/* Start channel transfer */
		dmadrv_dat.pdma->dma_chan [ch].config_ch =
			(DMAC_CHAN_FLOW_D_P2M | DMAC_CHAN_ENABLE | DMAC_SRC_PERIP(9) );
		
		sts = _NO_ERROR;
	}

	return sts;
}



/***********************************************************************
 *
 * Function: dma_setup_link_phy
 *
 * Purpose: Make a linked list entry (for physical addresses only)
 *
 * Processing:
 *     Place the source, destination, and DMA control word entries
 *     into the passed structure.
 * 
 * Parameters:
 *     plink       : Pointer to linked list entry
 *     dmasrc_phy  : Physical address of source data
 *     dmadest_phy : Physical address of destination data
 *     dma_ctrl    : DMA control word for the transfer
 *
 * Outputs: None
 *
 * Returns: Nothing
 *
 * Notes: None
 *
 **********************************************************************/
void dma_setup_link_phy(DMAC_LL_T *plink,
                        uint32_t *dmasrc_phy,
                        uint32_t *dmadest_phy,
                        uint32_t dma_ctrl)
{
	plink->dma_src = (uint32_t) dmasrc_phy;
	plink->dma_dest = (uint32_t) dmadest_phy;
	plink->next_ctrl = dma_ctrl;
}

/***********************************************************************
 *
 * Function: dma_setup_virt_link
 *
 * Purpose: Make a linked list entry (for virtual addresses only)
 *
 * Processing:
 *     Convert the source and destination addresses to physical
 *     addresses, Call dma_setup_link_phy() to place the source,
 *     destination, and DMA control word entries into the passed
 *     structure.
 * 
 * Parameters:
 *     plink        : Pointer to linked list entry
 *     dmasrc_virt  : Virtual address of source data
 *     dmadest_virt : Virtual address of destination data
 *     dma_ctrl     : DMA control word for the transfer
 *
 * Outputs: None
 *
 * Returns: Nothing
 *
 * Notes: None
 *
 **********************************************************************/

 /*
void dma_setup_virt_link(DMAC_LL_T *plink,
                         uint32_t *dmasrc_virt,
                         uint32_t *dmadest_virt,
                         uint32_t dma_ctrl)
{
	uint32_t *src_phy, *dest_phy;

	src_phy = (uint32_t *) cp15_map_virtual_to_physical(dmasrc_virt);
	dest_phy = (uint32_t *) cp15_map_virtual_to_physical(dmadest_virt);

	dma_setup_link_phy(plink, src_phy, dest_phy, dma_ctrl);
}
*/
/***********************************************************************
 *
 * Function: dma_enable_sync
 *
 * Purpose: Enable or disable SYNC logic for a specific peripheral
 *
 * Processing:
 *     For the passed peripheral, enable or disable the sync signals
 *     for it based on enable.
 * 
 * Parameters:
 *     periph : Must be a peripheral ID value of DMA_PER_xxx
 *     enable : '0' to disable, '!0' to enable
 *
 * Outputs: None
 *
 * Returns: Nothign
 *
 * Notes: None
 *
 **********************************************************************/
void dma_enable_sync(uint32_t periph,
                     uint32_t enable) 
{
	if (enable == 0) 
	{
		dmadrv_dat.pdma->sync |= periph;
	}
	else 
	{
		dmadrv_dat.pdma->sync &= ~periph;
	}
}

/***********************************************************************
 *
 * Function: dma_get_base
 *
 * Purpose: Return pointer to DMA registers
 *
 * Processing:
 *     Convert the source and destination addresses to physical
 *     addresses, Call dma_setup_link_phy() to place the source,
 *     destination, and DMA control word entries into the passed
 *     structure.
 * 
 * Parameters: None
 *
 * Outputs: None
 *
 * Returns: Pointer to DMA base registers
 *
 * Notes: None
 *
 **********************************************************************/
DMAC_REGS_T *dma_get_base(void) 
{
	return dmadrv_dat.pdma;
}
