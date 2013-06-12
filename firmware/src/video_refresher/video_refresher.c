/**
 * \name video_refresher.c 
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





/**************************************************************************************************/
void video_refresher_init()
{
	event_post(VIDEO_REFRESHER_EVENT, 32);
}

/**************************************************************************************************/
void video_refresher_event(void* subtype)
{
	DEBUG_PRINTF("vid event: %d\n", subtype);
}

/**************************************************************************************************/
void video_refresher_update()
{

}
