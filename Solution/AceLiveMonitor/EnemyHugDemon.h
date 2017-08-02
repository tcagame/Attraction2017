#pragma once
#include "Enemy.h"

class EnemyHugDemon : public Enemy {
public:
	EnemyHugDemon( const Vector& pos );
	virtual ~EnemyHugDemon( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

