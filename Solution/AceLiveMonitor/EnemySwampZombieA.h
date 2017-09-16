#pragma once
#include "Enemy.h"

class EnemySwampZombieA : public Enemy {
public:
	EnemySwampZombieA( const Vector& pos );
	virtual ~EnemySwampZombieA( );
public:
	void setSynchronousData( int camera_pos ) const;
	void damage( int force );
protected:
	void act( );
};

