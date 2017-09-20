#pragma once
#include "Event.h"

class EventRyugu : public Event {
public:
	EventRyugu( );
	virtual ~EventRyugu( );
public:
	void update( );
	bool isJoining( ) const;
	void join( PLAYER target );
};

