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
	bool isJoining( ) const;
	void join( PLAYER target );
protected:
	int getLeavePosX( ) const;
private:
	EnemyBossPtr _boss;
};

