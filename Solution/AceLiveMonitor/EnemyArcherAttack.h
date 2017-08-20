#pragma once
#include "Enemy.h"

class EnemyArcherAttack : public Enemy {
public:
	EnemyArcherAttack( const Vector& pos );
	virtual ~EnemyArcherAttack();
public:
	Chip getChip( ) const;
protected:
	void act( );
};

