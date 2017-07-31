#pragma once
#include "RockEnemy.h"
class RockEnemyGhost: public RockEnemy {
public:
	RockEnemyGhost( const Vector& pos );
	virtual ~RockEnemyGhost();
protected:
	void act( );
};

