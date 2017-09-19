#pragma once
#include "RockEnemyAttack.h"

class RockEnemyBossFireAttack : public RockEnemyAttack {
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
