/**
 * \name events.c 
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


static struct
{
	int head;
	int tail;
	volatile int count;
	event_t queue[MAX_EVENTS];
} event_queue;




/**************************************************************************************************/
void event_init()
{
	memset(&event_queue, 0, sizeof(event_queue));
}

/**************************************************************************************************/
bool event_post(event_type_t type, void *sub_type)
{
	if(event_queue.count >= MAX_EVENTS)
	{
		DEBUG_PRINT("WARN: event queue full!\n");
		return false;
	}
	event_t *evt = &event_queue.queue[event_queue.tail];
	evt->type = type;
	evt->subtype = sub_type;
	event_queue.tail = (event_queue.tail + 1) & (MAX_EVENTS-1);

	DISABLE_INTERRUPTS();
	++event_queue.count;
	ENABLE_INTERRUPTS();

	return true;
}


/**************************************************************************************************/
void event_wait(event_t *event_ptr)
{
	while(event_queue.count == 0) {}

	event_t *evt = &event_queue.queue[event_queue.head];
	event_ptr->type = evt->type;
	event_ptr->subtype = evt->subtype;
	event_queue.head = (event_queue.head + 1) & (MAX_EVENTS-1);

	DISABLE_INTERRUPTS();
	--event_queue.count;
	ENABLE_INTERRUPTS();
}

