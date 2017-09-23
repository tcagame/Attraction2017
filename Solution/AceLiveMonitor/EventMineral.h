#pragma once
#include "Event.h"
#include "smart_ptr.h"

PTR( EnemyBoss );

class EventMineral : public Event {
public:
	EventMineral( );
	virtual ~EventMineral( );
public:
	void update( );
	void join( PLAYER target );
private:
	EnemyBossPtr _boss;
	int _count;
};

