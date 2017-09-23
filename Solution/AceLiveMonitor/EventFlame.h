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
	void join( PLAYER target );
protected:
	int getLeavePosX( ) const;
private:
	EnemyBossPtr _boss;
};

