#pragma once
#include "RockEnemy.h"

class RockEnemyStoneFace: public RockEnemy {
public:
	RockEnemyStoneFace( const Vector& pos );
	virtual ~RockEnemyStoneFace( );
public:
	double getAnimTime( ) const;
	void dropItem( );
protected:
	void act( );
private:
	int _player_radius;
};

