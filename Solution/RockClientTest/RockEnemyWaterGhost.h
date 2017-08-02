#pragma once
#include "RockEnemy.h"
class RockEnemyWaterGhost :
	public RockEnemy {
public:
	RockEnemyWaterGhost( const Vector& pos );
	virtual ~RockEnemyWaterGhost( );
protected:
	void act( );
};

