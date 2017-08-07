#pragma once
#include "EnemyBoss.h"
class EnemyBossRock : public EnemyBoss {
public:
	EnemyBossRock( const Vector& pos );
	virtual ~EnemyBossRock( );
public:
	Chip getChip( ) const;
	Chip getChip2( ) const;
protected:
	void act( );
};

