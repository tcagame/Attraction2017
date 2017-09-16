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
	bool isFinished( ) const;
	bool isJoining( ) const;
	void join( PLAYER target );
private:
	EnemyBossPtr _boss;
};