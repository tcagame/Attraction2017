#pragma once
#include "Enemy.h"
class EnemyRedBirdAttack : public Enemy {
public:
	EnemyRedBirdAttack( const Vector& pos );
	virtual ~EnemyRedBirdAttack( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

