#pragma once
#include "RockEnemy.h"

class RockEnemyBat : public RockEnemy {
public:
	RockEnemyBat( const Vector& pos );
	virtual ~RockEnemyBat( );
public:
	double getAnimTime( ) const;
	void dropItem( );
protected:
	void act( );
private:
	int _player_radius;
};

