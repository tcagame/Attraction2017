#pragma once
#include "EnemyBoss.h"


class EnemyBossBloodDaemon : public EnemyBoss {
public:
	EnemyBossBloodDaemon( const Vector& pos );
	virtual ~EnemyBossBloodDaemon( );
public:
	Chip getChip( ) const;
	void dropItem( );
protected:
	void act( );
};

