#pragma once
#include "Enemy.h"

class EnemySwampZombieA : public Enemy {
public:
	EnemySwampZombieA( const Vector& pos );
	virtual ~EnemySwampZombieA( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
	void damage( int force );
protected:
	void act( );
};

