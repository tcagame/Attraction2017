#pragma once
#include "Event.h"

class EventRyugu : public Event {
public:
	EventRyugu( );
	virtual ~EventRyugu( );
public:
	void update( );
	void join( PLAYER target );
};

