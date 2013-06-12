/*
 * main.c
 *
 *  Created on: May 23, 2013
 *      Author: Reed
 */

#include <limits.h>


#include "MassStorageHost.h"
#include "fsusb_cfg.h"
#include "ff.h"



static void SetupHardware(void);
static void throughputTest(void);


#define RUNTIME_TIMER LPC_TIMER0

#define FRAME_SIZE (120*120*3)
#define MAX_FRAME_READS 128
#define PCLK_US (1e6f / 60e6f)

static uint8_t frameBuffer[FRAME_SIZE];

STATIC FATFS fatFS;	/* File system object */
STATIC FIL fileObj;	/* File object */


/** LPCUSBlib Mass Storage Class driver interface configuration and state information. This structure is
 *  passed to all Mass Storage Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_MS_Host_t FlashDisk_MS_Interface = {
	.Config = {
		.DataINPipeNumber       = 1,
		.DataINPipeDoubleBank   = false,

		.DataOUTPipeNumber      = 2,
		.DataOUTPipeDoubleBank  = false,
		.PortNumber = 0,
	},
};





/** Main program entry point. This routine configures the hardware required by the application, then
 *  calls the filesystem function to read files from USB Disk
 */
int main(void)
{
	SetupHardware();

	DEBUGOUT("Mass Storage Read Through-put test runnig.\r\n");

	throughputTest();

	DEBUGOUT("Test completed.\r\n");
	while (1) {}
}





/* Function to spin forever when there is an error */
static void die(FRESULT rc)
{
	DEBUGOUT("*******DIE %d*******\r\n", rc);
	while (1) {}/* Spin for ever */

}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
static void SetupHardware(void)
{
	Board_Init();
	USB_Init(FlashDisk_MS_Interface.Config.PortNumber, USB_MODE_Host);
	/* Hardware Initialization */
	Board_Debug_Init();

	/* Create a stdio stream for the serial port for stdin and stdout */
	Serial_CreateStream(NULL);


	Chip_TIMER_Init(RUNTIME_TIMER);
	//Chip_TIMER_TIMER_SetCountClockSrc(RUNTIME_TIMER, TIMER_CAPSRC_RISING_PCLK, 0);
	Chip_TIMER_PrescaleSet(RUNTIME_TIMER, 0);
}

/* Function to do the read/write to USB Disk */
static void throughputTest(void)
{
	FRESULT rc;		/* Result code */
	UINT br;



	f_mount(0, &fatFS);		/* Register volume work area (never fails) */

	rc = f_open(&fileObj, "test.bin", FA_READ);
	if (rc) {
		DEBUGOUT("Unable to open big_file.bin from USB Disk\r\n");
		die(rc);
	}

	int frameReads;
	uint32_t readTimes[MAX_FRAME_READS];

	Chip_TIMER_Enable(RUNTIME_TIMER);

	for(frameReads = 0; frameReads < MAX_FRAME_READS; ++frameReads)
	{
		RUNTIME_TIMER->TC = 0;
		/* Read a chunk of file */
		rc = f_read(&fileObj, frameBuffer, FRAME_SIZE, &br);
		if(rc != FR_OK)
		{
			DEBUGOUT("Error reading from file\r\n");
			die(rc);
		}
		else if(br != FRAME_SIZE)
		{
			break;
		}
		readTimes[frameReads] = RUNTIME_TIMER->TC;
		Board_UARTPutChar('.');
	}

	f_close(&fileObj);

	uint64_t sum = 0;
	uint32_t min = UINT32_MAX;
	uint32_t max = 0;
	float ave;

	for(int i = 0; i < frameReads; ++i)
	{
		sum += readTimes[i];
		if(readTimes[i] < min)
			min = readTimes[i];
		if(readTimes[i] > max)
			max = readTimes[i];
	}
	ave = (float)sum / (float)frameReads;

	printf("\n----------------------------\n");
	printf("Test Results\n");
	printf("----------------------------\n");
	printf("\tFrames read: %d\n", frameReads);
	printf("\tFrame size: %.3fkB\n", (float)FRAME_SIZE / 1000.0);
	printf("\tMin time: %.3fus\n", (float)min * PCLK_US);
	printf("\tMax time: %.3fus\n", (float)max * PCLK_US);
	printf("\tAve time: %.3fus\n", (float)ave * PCLK_US);
	printf("\n----------------------------\n");
	printf("All times\n");
	printf("----------------------------\n");
	for(int i = 0; i < frameReads; ++i)
	{
		printf("\t%02d: %.3fus\n", i,  (float)readTimes[i] * PCLK_US);
	}
	printf("----------------------------\n\n");

	DEBUGOUT("\r\nTest completed.\r\n");
	USB_Host_SetDeviceConfiguration(FlashDisk_MS_Interface.Config.PortNumber, 0);
}
