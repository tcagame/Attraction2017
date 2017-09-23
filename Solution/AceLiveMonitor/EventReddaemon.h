#pragma once
#include "Event.h"
#include "smart_ptr.h"

PTR( EnemyBoss );

class EventReddaemon : public Event {
public:
	EventReddaemon( );
	virtual ~EventReddaemon( );
public:
	void update( );
	void join( PLAYER target );
private:
	EnemyBossPtr _boss;
	int _count;
};