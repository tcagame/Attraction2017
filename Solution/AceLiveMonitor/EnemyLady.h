#pragma once
#include "Enemy.h"

class EnemyLady : public Enemy {
public:
	EnemyLady( const Vector& pos );
	virtual ~EnemyLady( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
};

