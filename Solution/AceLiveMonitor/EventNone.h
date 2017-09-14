#pragma once
#include "Event.h"
class EventNone : public Event {
public:
	EventNone( );
	virtual ~EventNone( );
public:
	void update( );
};

