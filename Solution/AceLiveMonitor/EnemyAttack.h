#pragma once
#include "Enemy.h"
class EnemyAttack : public Enemy {
public:
	EnemyAttack( const Vector& pos, const int chip_size, bool mass = true );
	virtual ~EnemyAttack( );
};

