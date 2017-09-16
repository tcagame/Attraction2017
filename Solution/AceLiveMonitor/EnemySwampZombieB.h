#pragma once
#include "Enemy.h"

class EnemySwampZombieB : public Enemy {
public:
	EnemySwampZombieB( const Vector& pos );
	virtual ~EnemySwampZombieB( );
public:
	void setSynchronousData( int camera_pos ) const;
	void damage( int force );
protected:
	void act( );
};

