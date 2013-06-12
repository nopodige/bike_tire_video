/**
 * \name main.c 
 *
 * \author Reed
 * \date Jun 12, 2013
 *
 * \brief
 *
 */


#include "common.h"



/**************************************************************************************************
 * \brief Program entry point
 */
int main()
{
	sys_init();

	DEBUG_PRINT("\nStarting BikeTireVideo Firmware\n");

	event_init();
	position_monitor_init();
	display_refresher_init();
	video_refresher_init();

	for(;;)
	{
		event_t event;

		event_wait(&event);

		switch(event.type)
		{
		case POSITION_MONITOR_EVENT:
			position_monitor_event(event.subtype);
			break;
		case POSITION_UPDATE_EVENT:
			position_monitor_update();
			break;
		case VIDEO_REFRESHER_EVENT:
			video_refresher_event(event.subtype);
			break;
		case VIDEO_UPDATE_EVENT:
			video_refresher_update();
			break;
		case DISPLAY_REFRESHER_EVENT:
			video_refresher_event(event.subtype);
			break;
		case DISPLAY_UPDATE_EVENT:
			video_refresher_update();
			break;
		default:
			DEBUG_PRINTF("Unknown event: %d, %d\n", event.type, event.subtype);

		}
	}


}
