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
	enum PHASE {
		PHASE_NORMAL,
		PHASE_FINISHED,
		PHASE_WAIT,
	};
private:
	PHASE _phase;
	EnemyBossPtr _boss;
	int _count;
};