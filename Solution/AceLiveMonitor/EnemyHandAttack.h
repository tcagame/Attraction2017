#pragma once
#include "Enemy.h"

class EnemyHandAttack : public Enemy {
public:
	EnemyHandAttack( const Vector& pos );
	virtual ~EnemyHandAttack( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

