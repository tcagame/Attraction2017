#pragma once
#include "RockEnemy.h"

class RockEnemyCloud : public RockEnemy {
public:
	RockEnemyCloud( const Vector& pos );
	virtual ~RockEnemyCloud( );
public:
	double getAnimTime( ) const;
	void dropItem( );
protected:
	void act( );
private:
	int _player_radius;
};

