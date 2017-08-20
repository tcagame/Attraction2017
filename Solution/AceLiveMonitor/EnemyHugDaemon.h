#pragma once
#include "Enemy.h"

class EnemyHugDaemon : public Enemy {
public:
	EnemyHugDaemon( const Vector& pos );
	virtual ~EnemyHugDaemon( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

