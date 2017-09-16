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
private:
	EnemyBossPtr _boss;
};