#pragma once
#include "Event.h"

class EventCall : public Event {
public:
	EventCall( );
	virtual ~EventCall( );
public:
	void update( );
	bool isFinished( ) const;
	void join( PLAYER target );
};

