#pragma once
#include "RockEnemy.h"
class RockEnemyGhost: public RockEnemy {
public:
	RockEnemyGhost( const Vector& pos );
	virtual ~RockEnemyGhost( );
public:
	double getAnimTime( ) const;
	void dropItem( );
protected:
	void act( );
private:
	int _player_radius;
};

