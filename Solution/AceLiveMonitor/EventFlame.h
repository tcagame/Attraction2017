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
	bool isFinished( ) const;
	bool isJoining( ) const;
	void join( PLAYER target );
private:
	EnemyBossPtr _boss;
};

