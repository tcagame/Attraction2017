#pragma once
#include "RockEnemy.h"

class RockEnemyStone : public RockEnemy {
public:
	RockEnemyStone( const Vector& pos );
	virtual ~RockEnemyStone( );
public:
	double getAnimTime( ) const;
	void dropItem( );
	ModelMV1Ptr getModel( );
protected:
	void act( );
private:
	int _player_radius;
	double _rot;
};
