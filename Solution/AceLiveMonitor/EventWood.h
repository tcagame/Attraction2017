#pragma once
#include "Event.h"
#include "smart_ptr.h"

PTR( EnemyBoss );

class EventWood : public Event {
public:
	EventWood( );
	virtual ~EventWood( );
public:
	void update( );
	bool isFinished( ) const;
	bool isJoining( ) const;
	void join( PLAYER target );
private:
	EnemyBossPtr _boss;
};

