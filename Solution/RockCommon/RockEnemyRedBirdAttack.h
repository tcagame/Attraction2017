#pragma once
#include "RockEnemyAttack.h"

class RockEnemyRedBirdAttack : public RockEnemyAttack {
public:
	RockEnemyRedBirdAttack( const Vector pos );
	virtual ~RockEnemyRedBirdAttack( );
protected:
	void act( );
	double getAnimTime( ) const;
};

