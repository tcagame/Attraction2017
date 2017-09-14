#pragma once
#include "Event.h"
class EventReddaemon : public Event {
public:
	EventReddaemon( );
	virtual ~EventReddaemon( );
public:
	void update( );
};