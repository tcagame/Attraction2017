#pragma once
#include "RockEnemy.h"
class RockEnemyAttack : public RockEnemy {
public:
	RockEnemyAttack( const Vector& pos, DOLL id, int hp, int force = 1, int radius = 10, int height = 30, bool mass = true, bool head = true );
	virtual ~RockEnemyAttack( );
};

