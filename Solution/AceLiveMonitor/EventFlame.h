#pragma once
#include "Event.h"
#include "smart_ptr.h"

PTR( EnemyBoss );

class EventFlame : public Event {
public:
	EventFlame( );
	virtual ~EventFlame( );
public:
	void update( );
private:
	EnemyBossPtr _boss;
};

