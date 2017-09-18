#pragma once
#include "RockEnemyBoss.h"

class RockEnemyBossReaDaemon : public RockEnemyBoss {
public:
	RockEnemyBossReaDaemon( const Vector& pos );
	virtual ~RockEnemyBossReaDaemon( );
public:
	double getAnimTime( ) const;
protected:
	void act( );
};