#pragma once
#include "Enemy.h"
class EnemyHellFire : public Enemy {
public:
	EnemyHellFire( const Vector& pos );
	virtual ~EnemyHellFire( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

