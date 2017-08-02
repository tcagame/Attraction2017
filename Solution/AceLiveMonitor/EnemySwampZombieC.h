#pragma once
#include "Enemy.h"

class EnemySwampZombieC : public Enemy {
public:
	EnemySwampZombieC( const Vector& pos );
	virtual ~EnemySwampZombieC( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

