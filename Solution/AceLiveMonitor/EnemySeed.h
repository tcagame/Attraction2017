#pragma once
#include "Enemy.h"

class EnemySeed : public Enemy {
public:
	EnemySeed( const Vector& pos );
	virtual ~EnemySeed( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

