/*
 * main.c
 *
 *  Created on: May 23, 2013
 *      Author: Reed
 */

#include <limits.h>

#include "board.h"
#include "led_tests.h"


static void SetupHardware(void);
static void ledTest(void);




static uint8_t ledCache[LED_CACHE_SIZE];

extern void WS2811_sendData(uint8_t *buffer, uint16_t buff_size, void *PORT);

static inline void popuateLedCache();
static inline void generateCacheByte(uint16_t cachePos,
		uint8_t led0E, uint8_t led0O,
		uint8_t led1E, uint8_t led1O,
		uint8_t led2E, uint8_t led2O,
		uint8_t led3E, uint8_t led3O);

#define LED_GPIO LPC_GPIO2
#define LED_DATA_PORT_BASE ((uint8_t*)&LED_GPIO->PIN)
#define LED_DATA_PORT *(LED_DATA_PORT_BASE)

#define FRAME_TIMER LPC_TIMER0
#define FRAME_TIMER_MATCH_NUM 0
#define FRAME_TIMER_MATCH_VAL 2400000 // 2400000/60e6 = 0.04s (25Hz)

#define RUNTIME_TIMER LPC_TIMER1



/** Main program entry point. This routine configures the hardware required by the application, then
 *  calls the filesystem function to read files from USB Disk
 */
int main(void)
{
	SetupHardware();

	DEBUGOUT("LED Strip test running.\r\n");

	ledTest();

	DEBUGOUT("Test completed.\r\n");
	while (1) {}
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
static void SetupHardware(void)
{
	Board_Init();

	/* Hardware Initialization */
	Board_Debug_Init();

	/* Create a stdio stream for the serial port for stdin and stdout */
	Serial_CreateStream(NULL);

}



static void ledTest(void)
{
	Chip_TIMER_Init(FRAME_TIMER);
	Chip_TIMER_PrescaleSet(FRAME_TIMER, 0);
	Chip_TIMER_SetMatch(FRAME_TIMER, FRAME_TIMER_MATCH_NUM, FRAME_TIMER_MATCH_VAL);
	Chip_TIMER_ResetOnMatchEnable(FRAME_TIMER, FRAME_TIMER_MATCH_NUM);
	Chip_TIMER_MatchEnableInt(FRAME_TIMER, FRAME_TIMER_MATCH_NUM);
	//	/* Enable Interrupt for TIMER0 channel */
	//	/* Priority = 1 */
	NVIC_SetPriority(TIMER0_IRQn, 1);
	//	/* Enable Interrupt for TIMER0 channel */
	NVIC_EnableIRQ(TIMER0_IRQn);

	Chip_TIMER_Init(RUNTIME_TIMER);
	Chip_TIMER_PrescaleSet(RUNTIME_TIMER, 0); // gives ms resolution
	Chip_TIMER_Enable(RUNTIME_TIMER);

	//	LED_GPIO->MASK = ~0xff;
	LED_GPIO->DIR = 0xff;

	Chip_TIMER_Enable(FRAME_TIMER);
	for(;;)
	{
		//Board_UARTPutChar('.');
		NVIC_DisableIRQ(TIMER0_IRQn);
		popuateLedCache();
		WS2811_sendData(ledCache, LED_CACHE_SIZE, LED_DATA_PORT_BASE);
		NVIC_EnableIRQ(TIMER0_IRQn);
	}
}





static inline void popuateLedCache()
{
	//DEBUGOUT("populating led cache...\n");
	uint16_t cachePos = 0;

	for(int i = 0; i < LED_BUFFER_SIZE; i += 2)
	{
		const uint8_t led0E = ledBuffer[0][i];
		const uint8_t led0O = ledBuffer[0][i+1];
		const uint8_t led1E = ledBuffer[1][i];
		const uint8_t led1O = ledBuffer[1][i+1];
		const uint8_t led2E = ledBuffer[2][i];
		const uint8_t led2O = ledBuffer[2][i+1];
		const uint8_t led3E = ledBuffer[3][i];
		const uint8_t led3O = ledBuffer[3][i+1];

		generateCacheByte(cachePos, led0E, led0O, led1E, led1O, led2E, led2O, led3E, led3O);
		cachePos += 8;
	}

	//	uint8_t *cPtr = ledCache;
	//	DEBUGOUT("led cache layout:\n");
	//	for(int i = 0; i < LED_COUNT; ++i)
	//	{
	//		DEBUGOUT("led %d:\n", i);
	//		for(int k = 0; k < 3; k++)
	//		{
	//			static const char* comp[] = {"RED  ", "GREEN", "BLUE "};
	//
	//			DEBUGOUT("\tcomponent %s: ", comp[k]);
	//			for(int l = 0; l < 8; ++l)
	//			{
	//				for(int j = 0; j < LED_BYTES_PER_BIT; ++j)
	//				{
	//					DEBUGOUT("%02X", *cPtr++);
	//				}
	//				DEBUGOUT(" ");
	//			}
	//			DEBUGOUT("\n");
	//		}
	//	}

	//DEBUGOUT("populated.\n");

}

static inline void generateCacheByte(uint16_t cachePos,
		uint8_t led0E, uint8_t led0O,
		uint8_t led1E, uint8_t led1O,
		uint8_t led2E, uint8_t led2O,
		uint8_t led3E, uint8_t led3O)
{
	uint8_t *cPtr = &ledCache[cachePos];

	for(int i = 0; i < 8; ++i)
	{
		const uint8_t l0E = led0E & 0x80;
		const uint8_t l0O = led0O & 0x80;
		const uint8_t l1E = led1E & 0x80;
		const uint8_t l1O = led1O & 0x80;
		const uint8_t l2E = led2E & 0x80;
		const uint8_t l2O = led2O & 0x80;
		const uint8_t l3E = led3E & 0x80;
		const uint8_t l3O = led3O & 0x80;

		*cPtr++ = (l0E >> 7) | (l0O >> 6) | (l1E >> 5) | (l1O >> 4) | (l2E >> 3) | (l2O >> 2) | (l3E >> 1) | (l3O >> 0);

		led0E <<= 1; led0O <<= 1;
		led1E <<= 1; led1O <<= 1;
		led2E <<= 1; led2O <<= 1;
		led3E <<= 1; led3O <<= 1;
	}
}

void TIMER0_IRQHandler()
{
	populateLedBuffer();
	FRAME_TIMER->IR = TIMER_MATCH_INT(FRAME_TIMER_MATCH_NUM);
}



