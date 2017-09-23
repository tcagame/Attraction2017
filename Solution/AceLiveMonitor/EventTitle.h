#pragma once
#include "Event.h"
class EventTitle : public Event {
public:
	EventTitle( );
	virtual ~EventTitle( );
public:
	void update( );
	void join( PLAYER target );
};

