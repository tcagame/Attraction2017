#pragma once
#include "Enemy.h"
class EnemyHellFire : public Enemy {
public:
	EnemyHellFire( const Vector& pos );
	virtual ~EnemyHellFire( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
};

