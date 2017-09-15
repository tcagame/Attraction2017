#pragma once
#include "RockEnemy.h"

class RockEnemyMoth : public RockEnemy {
public:
	RockEnemyMoth( const Vector& pos );
	virtual ~RockEnemyMoth( );
public:
	double getAnimTime( ) const;
	void dropItem( );
protected:
	void act( );
private:
	int _player_radius;
};

