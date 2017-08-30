#pragma once
#include "RockEnemyBoss.h"

class RockEnemyBossRock : public RockEnemyBoss {
public:
	RockEnemyBossRock( const Vector& pos );
	virtual ~RockEnemyBossRock( );
public:
	double getAnimTime( ) const;
	void dropItem( );
protected:
	void act( );
};

