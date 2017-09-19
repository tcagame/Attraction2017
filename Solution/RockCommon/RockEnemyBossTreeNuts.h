#pragma once
#include "RockEnemyAttack.h"

class RockEnemyBossTreeNuts : public RockEnemyAttack {
public:
	RockEnemyBossTreeNuts( const Vector pos );
	virtual ~RockEnemyBossTreeNuts( );
public:
	void act( );
	double getAnimTime( ) const;
	ModelMV1Ptr getModel( ) const;
private:
	int _handle;
	int _player_radius;
};
