#pragma once
#include "Event.h"
class EventShop : public Event {
public:
	EventShop( );
	virtual ~EventShop( );
public:
	void update( );
	bool isFinished( ) const;
	bool isJoining( ) const;
	void join( PLAYER target );
};

