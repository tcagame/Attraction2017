#pragma once
#include "RockEnemyBoss.h"

class RockEnemyBossRedDaemon : public RockEnemyBoss {
public:
	RockEnemyBossRedDaemon( const Vector& pos );
	virtual ~RockEnemyBossRedDaemon( );
public:
	double getAnimTime( ) const;
protected:
	void act( );
};