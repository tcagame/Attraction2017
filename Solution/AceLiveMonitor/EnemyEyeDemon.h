#pragma once
#include "Enemy.h"

class EnemyEyeDemon : public Enemy {
public:
	EnemyEyeDemon( const Vector& pos );
	virtual ~EnemyEyeDemon( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

