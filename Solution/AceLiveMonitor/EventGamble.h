#pragma once
#include "Event.h"
class EventGamble: public Event {
public:
	EventGamble( );
	virtual ~EventGamble( );
public:
	void update( );
	bool isFinished( ) const;
	bool isJoining( ) const;
	void join( PLAYER target );
};

