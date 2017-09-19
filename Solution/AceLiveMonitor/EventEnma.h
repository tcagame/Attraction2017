#pragma once
#include "Event.h"
class EventEnma : public Event {
public:
	EventEnma( );
	virtual ~EventEnma( );
public:
	void update( );
	bool isJoining( ) const;
	void join( PLAYER target );
private:
	bool _audience;
};

