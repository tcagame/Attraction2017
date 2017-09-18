#pragma once
#include "RockEnemy.h"

class RockEnemyBossFireAttack : public RockEnemy {
public:
	RockEnemyBossFireAttack( const Vector pos );
	virtual ~RockEnemyBossFireAttack( );
public:
	void act( );
	double getAnimTime( ) const;
	ModelMV1Ptr getModel( ) const;
private:
	bool _shot;
	int _handle;
};
