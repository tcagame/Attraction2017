#pragma once
#include "RockEnemy.h"

class RockEnemyFaceAndHand : public RockEnemy {
public:
	RockEnemyFaceAndHand( const Vector& pos );
	virtual ~RockEnemyFaceAndHand( );
public:
	double getAnimTime( ) const;
	void dropItem( );
protected:
	void act( );
private:
	int _player_radius;
};

