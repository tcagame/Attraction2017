#pragma once
#include "Event.h"
class EventTitle : public Event {
public:
	EventTitle( );
	virtual ~EventTitle( );
public:
	void update( );
	bool isJoining( ) const;
	void join( PLAYER target );
};

