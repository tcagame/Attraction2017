#pragma once
#include "Enemy.h"

class EnemyArcher : public Enemy {
public:
	EnemyArcher( const Vector& pos );
	virtual ~EnemyArcher( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

