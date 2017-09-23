#pragma once
#include "Event.h"
class EventGamble: public Event {
public:
	EventGamble( );
	virtual ~EventGamble( );
public:
	void update( );
	void join( PLAYER target );
private:
	bool _audience;
};

