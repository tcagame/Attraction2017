#pragma once
#include "Enemy.h"

class EnemyShishimaiDemon : public Enemy {
public:
	EnemyShishimaiDemon( const Vector& pos );
	virtual ~EnemyShishimaiDemon( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

