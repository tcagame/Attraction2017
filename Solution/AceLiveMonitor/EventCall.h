#pragma once
#include "Event.h"

class EventCall : public Event {
public:
	EventCall( );
	virtual ~EventCall( );
public:
	void update( );
};

