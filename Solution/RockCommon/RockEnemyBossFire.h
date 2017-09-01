#pragma once
#include "RockEnemyBoss.h"
class RockEnemyBossFire : public RockEnemyBoss {
public:
	RockEnemyBossFire( const Vector& pos );
	virtual ~RockEnemyBossFire( );
public:
	double getAnimTime( ) const;
	void dropItem( );
protected:
	void act( );
};

