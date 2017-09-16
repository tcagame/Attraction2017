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
	bool isFinished( ) const;
	bool isJoining( ) const;
	void join( PLAYER target );
private:
	EnemyBossPtr _boss;
};

