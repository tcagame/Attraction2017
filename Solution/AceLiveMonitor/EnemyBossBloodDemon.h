#pragma once
#include "EnemyBoss.h"


class EnemyBossBloodDemon : public EnemyBoss {
public:
	EnemyBossBloodDemon( const Vector& pos );
	virtual ~EnemyBossBloodDemon( );
public:
	Chip getChip( ) const;
	void dropItem( );
protected:
	void act( );
};

