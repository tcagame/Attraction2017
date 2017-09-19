#pragma once
#include "Event.h"
class EventBudha : public Event {
public:
	EventBudha( );
	virtual ~EventBudha( );
public:
	void update( );
	bool isJoining( ) const;
	void join( PLAYER target );
};

