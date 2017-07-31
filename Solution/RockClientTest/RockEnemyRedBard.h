#pragma once
#include "RockEnemy.h"

class RockEnemyRedBard : public RockEnemy {
public:
	RockEnemyRedBard( const Vector& pos );
	virtual ~RockEnemyRedBard( );
protected:
	void act( );
};

