#pragma once
#include "Enemy.h"

class EnemySwampZombieC : public Enemy {
public:
	EnemySwampZombieC( const Vector& pos );
	virtual ~EnemySwampZombieC( );
public:
	Chip getChip( ) const;
	void damage( int force );
protected:
	void act( );
};

