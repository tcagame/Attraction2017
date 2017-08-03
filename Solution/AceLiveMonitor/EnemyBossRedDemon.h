#pragma once
#include "EnemyBoss.h"
class EnemyBossRedDemon : public EnemyBoss {
public:
	EnemyBossRedDemon( const Vector& pos );
	virtual ~EnemyBossRedDemon( );
public:
	Chip getChip( ) const;
	Chip getChip2( ) const;
protected:
	void act( );
};

