/*
 * led_tests.c
 *
 *  Created on: Jun 9, 2013
 *      Author: Reed
 */

#include <string.h>
#include "board.h"
#include "led_tests.h"


uint8_t ledBuffer[LED_STRIPS][LED_BUFFER_SIZE];

typedef void (*ledTest_t)(void);
typedef struct
{
	ledTest_t func;
	int runTime;
	char *desc;
} ledTestInfo_t;



static void ledTest_RGB();
static void ledTest_EvenOdd();
static void ledTest_EvenOdd2();
static void ledTest_Color();
static void ledTest_Color2();


#define ADD_TEST(name, time, desc) {ledTest_ ## name, time, desc}

static ledTestInfo_t tests[] = {
		//	ADD_TEST(RGB, 10, "RGB Test"),
		ADD_TEST(EvenOdd, 10, "EvenOdd Test"),
		ADD_TEST(EvenOdd2, 10, "EvenOdd2 Test"),
		ADD_TEST(Color, 10, "Color Test"),
		ADD_TEST(Color2, 10, "Color Test"),
};

static int currentTest = 0;
static int testTimer = 0;
static int frameCounter = 0;

void populateLedBuffer()
{
	--frameCounter;

	if(frameCounter <= 0)
	{
		frameCounter = 25;
		--testTimer;
	}

	if(testTimer <= 0)
	{
		++currentTest;
		if(currentTest >= sizeof(tests)/sizeof(ledTestInfo_t))
			currentTest = 0;
		DEBUGOUT("\nrunning: %s\n", tests[currentTest].desc);
		testTimer = tests[currentTest].runTime;

		//	DEBUGOUT("led buffer layout:\n");
		//	for(int i = 0; i < 4; ++i)
		//	{
		//		DEBUGOUT("\nstrip %d even: ", i);
		//		for(int j = 0; j < LED_BUFFER_SIZE; j += 6)
		//		{
		//			DEBUGOUT("%02X%02X%02X ", ledBuffer[i][j], ledBuffer[i][j+2], ledBuffer[i][j+4]);
		//		}
		//		DEBUGOUT("\nstrip %d odd : ", i);
		//		for(int j = 0; j < LED_BUFFER_SIZE; j += 6)
		//		{
		//			DEBUGOUT("%02X%02X%02X ", ledBuffer[i][j+1], ledBuffer[i][j+3], ledBuffer[i][j+5]);
		//		}
		//	}

		//DEBUGOUT("populated.\n");
	}

	tests[currentTest].func();
}


static void ledTest_RGB()
{
	for(int j = 0; j < 4; ++j)
	{
		for(int k = 0; k < 3; ++k)
		{
			uint8_t val = 0;

			if(j == k)
				val = 0xFF;
			else if(j ==3 )
				val = 0x7F;

			for(int i = k*2; i < LED_BUFFER_SIZE; i +=6)
			{
				ledBuffer[j][i] = val;
				ledBuffer[j][i+1] = val;
			}
		}
	}

}

static void ledTest_EvenOdd()
{
	static uint8_t toggle = 0;
	static uint8_t counter = 0;

	for(int j = 0; j < 4; ++j)
	{
		for(int k = 0; k < 3; ++k)
		{
			uint8_t val = 0;

			if(j == k)
				val = 0xFF;
			else if(j ==3 )
				val = 0x7F;

			for(int i = k*2; i < LED_BUFFER_SIZE; i +=6)
			{
				if(toggle)
				{
					ledBuffer[j][i] = val;
					ledBuffer[j][i+1] = 0;
				}
				else
				{
					ledBuffer[j][i] = 0;
					ledBuffer[j][i+1] = val;
				}
			}
		}
	}
	if(++counter == 12)
	{
		toggle = !toggle;
		counter = 0;
	}
}

static void ledTest_EvenOdd2()
{
	static int counter = 0;
	static uint8_t toggle = 1;

	memset(ledBuffer, 0, sizeof(ledBuffer));


	for(int j = 0; j < 3; ++j)
	{
		ledBuffer[j][((counter/2))*6 + (counter&1) + j*2] = 0xFF;
	}

	ledBuffer[3][((counter/2))*6 + (counter&1) + 0] = 0x7F;
	ledBuffer[3][((counter/2))*6 + (counter&1) + 2] = 0x7F;
	ledBuffer[3][((counter/2))*6 + (counter&1) + 4] = 0x7F;

	if(toggle)
	{
		if(++counter >= 60)
		{
			counter = 58;
			toggle = !toggle;
		}
	}
	else
	{
		if(--counter <= -1)
		{
			counter = 1;
			toggle = !toggle;
		}
	}
}

static void ledTest_Color()
{
	memset(ledBuffer, 0, sizeof(ledBuffer));

	static int counter = 0;
	static uint32_t c = 0;

	for(int i = 1; i <= 20; ++i)
	{
		int indx = ((i - 20/2) + counter) % (4*60);

		uint32_t color;

		color = (c +((i - 20/2)*100)) % (256*256*256);


		const uint8_t strip = indx/60;
		const uint8_t pixel = indx % 60;

		ledBuffer[strip][((pixel/2))*6 + (pixel&1) + 0] = (color >> 8) & 0xFF; // G
		ledBuffer[strip][((pixel/2))*6 + (pixel&1) + 2] = (color >> 0) & 0xFF; // R
		ledBuffer[strip][((pixel/2))*6 + (pixel&1) + 4] = (color >> 16) & 0xFF; // B
	}

	c += 10000;
	if(c > 256*256*256)
		c = 0;

	if(++counter >= 4*60)
	{
		counter = 0;
	}
}

static void ledTest_Color2()
{
	memset(ledBuffer, 0, sizeof(ledBuffer));

	static uint32_t color = 0;

	for(int i = 0; i <= 4*60; ++i)
	{

		const uint8_t strip = i/60;
		const uint8_t pixel = i % 60;

		ledBuffer[strip][((pixel/2))*6 + (pixel&1) + 0] = (color >> 8) & 0xFF; // G
		ledBuffer[strip][((pixel/2))*6 + (pixel&1) + 2] = (color >> 0) & 0xFF; // R
		ledBuffer[strip][((pixel/2))*6 + (pixel&1) + 4] = (color >> 16) & 0xFF; // B
	}

	color += 500;
	if(color > 256*256*256)
		color = 0;
}
