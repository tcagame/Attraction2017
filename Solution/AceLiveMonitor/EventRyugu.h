#pragma once
#include "Event.h"

class EventRyugu : public Event {
public:
	EventRyugu( );
	virtual ~EventRyugu( );
public:
	void update( );
	bool isFinished( ) const;
	bool isJoining( ) const;
	void join( PLAYER target );
};

