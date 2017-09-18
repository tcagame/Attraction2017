#pragma once
#include "RockEnemyBoss.h"

class RockEnemyLittleRedDaemon : public RockEnemyBoss {
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

