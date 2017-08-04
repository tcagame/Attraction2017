#pragma once
#include "Enemy.h"

class EnemyWind : public Enemy {
public:
	EnemyWind( const Vector& pos );
	virtual ~EnemyWind( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

