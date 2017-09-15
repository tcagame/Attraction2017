#pragma once
#include "RockEnemy.h"

class RockEnemyChivil : public RockEnemy {
public:
	RockEnemyChivil( const Vector& pos );
	virtual ~RockEnemyChivil( );
public:
	double getAnimTime( ) const;
	void dropItem( );
protected:
	void act( );
private:
	int _player_radius;
};

