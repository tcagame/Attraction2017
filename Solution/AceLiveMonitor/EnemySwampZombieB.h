#pragma once
#include "Enemy.h"

class EnemySwampZombieB : public Enemy {
public:
	EnemySwampZombieB( const Vector& pos );
	virtual ~EnemySwampZombieB( );
public:
	Chip getChip( ) const;
	void damage( int force );
protected:
	void act( );
};

