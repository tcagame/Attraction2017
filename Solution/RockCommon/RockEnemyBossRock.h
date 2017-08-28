#pragma once
#include "RockEnemy.h"
class RockEnemyBossRock : public RockEnemy {
public:
	RockEnemyBossRock( const Vector& pos );
	virtual ~RockEnemyBossRock( );
public:
	double getAnimTime( ) const;
	void dropItem( );
protected:
	void act( );
};

