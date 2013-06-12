/*
 * led_tests.h
 *
 *  Created on: Jun 9, 2013
 *      Author: Reed
 */

#ifndef LED_TESTS_H_
#define LED_TESTS_H_



#define LED_COUNT 30
#define LED_COMPONENTS 3
#define LED_BIT_PER_COMPONENT 8
#define LED_CACHE_SIZE (LED_BIT_PER_COMPONENT*LED_COMPONENTS*LED_COUNT)

#define LED_STRIPS 4
#define LED_PER_STRIP 60
#define LED_BUFFER_SIZE  (LED_PER_STRIP*LED_COMPONENTS)


extern uint8_t ledBuffer[LED_STRIPS][LED_BUFFER_SIZE];

void populateLedBuffer();


#endif /* LED_TESTS_H_ */
