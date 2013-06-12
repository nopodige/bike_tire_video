/**
 * \name events.h 
 *
 * \author Reed
 * \date Jun 12, 2013
 *
 * \brief
 *
 * \desc
 *
 */
#ifndef _EVENTS_H_
#define _EVENTS_H_

#include "chip.h"



typedef enum
{
	POSITION_MONITOR_EVENT,
	POSITION_UPDATE_EVENT,
	VIDEO_REFRESHER_EVENT,
	VIDEO_UPDATE_EVENT,
	DISPLAY_REFRESHER_EVENT,
	DISPLAY_UPDATE_EVENT,
} event_type_t;


typedef struct
{
	event_type_t type;
	void *subtype;
} event_t;


/**************************************************************************************************
 * \brief
 *
 * \param
 * \return
 */
void event_init();

/**************************************************************************************************
 * \brief
 *
 * \param
 * \return
 */
bool event_post(event_type_t type, void *sub_type);


/**************************************************************************************************
 * \brief
 *
 * \param
 * \return
 */
void event_wait(event_t *event_ptr);


#endif /* _EVENTS_H_ */
