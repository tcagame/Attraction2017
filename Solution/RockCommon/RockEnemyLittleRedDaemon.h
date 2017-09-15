#pragma once
#include "RockEnemy.h"

class RockEnemyLittleRedDaemon : public RockEnemy {
public:
	RockEnemyLittleRedDaemon( const Vector& pos );
	virtual ~RockEnemyLittleRedDaemon( );
public:
	double getAnimTime( ) const;
	void dropItem( );
protected:
	void act( );
private:
	int _player_radius;
};

