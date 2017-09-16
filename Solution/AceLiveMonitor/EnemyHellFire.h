#pragma once
#include "Enemy.h"
class EnemyHellFire : public Enemy {
public:
	EnemyHellFire( const Vector& pos );
	virtual ~EnemyHellFire( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
};

