#pragma once
#include "Event.h"
class EventLake : public Event {
public:
	EventLake( );
	virtual ~EventLake( );
public:
	void update( );
	bool isFinished( ) const;
	bool isJoining( ) const;
	void join( PLAYER target );
};

