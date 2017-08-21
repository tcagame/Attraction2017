#pragma once
#include "Enemy.h"

class EnemySwampZombieC : public Enemy {
public:
	EnemySwampZombieC( const Vector& pos );
	virtual ~EnemySwampZombieC( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
	void damage( int force );
protected:
	void act( );
};

