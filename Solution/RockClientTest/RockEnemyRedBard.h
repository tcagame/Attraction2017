#pragma once
#include "RockEnemy.h"

class RockEnemyRedBard : public RockEnemy {
public:
	RockEnemyRedBard( const Vector& pos );
	virtual ~RockEnemyRedBard( );
public:
	double getAnimTime( ) const;
protected:
	void act( );
};

