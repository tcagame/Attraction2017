#pragma once
#include "Enemy.h"
class EnemyBoss : public Enemy {
public:
	EnemyBoss( const Vector& pos, const int chip_size );
	virtual ~EnemyBoss( );
};
