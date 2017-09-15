#pragma once
#include "RockEnemy.h"

class RockEnemySmallFrog : public RockEnemy {
public:
	RockEnemySmallFrog( const Vector& pos );
	virtual ~RockEnemySmallFrog( );
public:
	double getAnimTime( ) const;
	void dropItem( );
protected:
	void act( );
private:
	int _player_radius;
};

