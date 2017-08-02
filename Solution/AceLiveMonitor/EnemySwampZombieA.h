#pragma once
#include "Enemy.h"

class EnemySwampZombieA : public Enemy {
public:
	EnemySwampZombieA( const Vector& pos );
	virtual ~EnemySwampZombieA( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

