#pragma once
#include "Enemy.h"

class EnemyLady : public Enemy {
public:
	EnemyLady( const Vector& pos );
	virtual ~EnemyLady( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

