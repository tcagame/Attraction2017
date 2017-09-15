#pragma once
#include "RockEnemy.h"

class RockEnemySkeleton : public RockEnemy {
public:
	RockEnemySkeleton( const Vector& pos );
	virtual ~RockEnemySkeleton( );
public:
	double getAnimTime( ) const;
	void dropItem( );
protected:
	void act( );
private:
	int _player_radius;
};

