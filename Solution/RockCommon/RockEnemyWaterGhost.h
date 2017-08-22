#pragma once
#include "RockEnemy.h"
class RockEnemyWaterGhost : public RockEnemy {
public:
	RockEnemyWaterGhost( const Vector& pos );
	virtual ~RockEnemyWaterGhost( );
public:
	double getAnimTime( ) const;
	void dropItem( );
protected:
	void act( );
};

