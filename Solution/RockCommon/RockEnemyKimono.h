#pragma once
#include "RockEnemy.h"

class RockEnemyKimono : public RockEnemy {
public:
	RockEnemyKimono( const Vector& pos );
	virtual ~RockEnemyKimono( );
public:
	double getAnimTime( ) const;
	void dropItem( );
protected:
	void act( );
private:
	int _player_radius;
};

