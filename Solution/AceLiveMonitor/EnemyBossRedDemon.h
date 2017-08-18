#pragma once
#include "EnemyBoss.h"

PTR( Enemy );

class EnemyBossRedDemon : public EnemyBoss {
public:
	EnemyBossRedDemon( const Vector& pos );
	virtual ~EnemyBossRedDemon( );
public:
	Chip getChip( ) const;
	Chip getChip2( ) const;
	void dropItem( );
protected:
	void act( );
};

