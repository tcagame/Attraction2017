#pragma once
#include "Enemy.h"

class EnemyLady : public Enemy {
public:
	EnemyLady( const Vector& pos );
	virtual ~EnemyLady( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
};

