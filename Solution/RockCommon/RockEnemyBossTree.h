#pragma once
#include "RockEnemyBoss.h"
class RockEnemyBossTree : public RockEnemyBoss {
public:
	RockEnemyBossTree( const Vector& pos );
	virtual ~RockEnemyBossTree( );
public:
	double getAnimTime( ) const;
	void dropItem( );
protected:
	void act( );
};

