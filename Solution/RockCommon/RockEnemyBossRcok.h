#pragma once
#include "RockEnemy.h"
class RockEnemyBossRcok : public RockEnemy {
public:
	RockEnemyBossRcok( const Vector& pos );
	virtual ~RockEnemyBossRcok( );
public:
	double getAnimTime( ) const;
	void dropItem( );
protected:
	void act( );
};

