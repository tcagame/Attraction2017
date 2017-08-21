#pragma once
#include "Enemy.h"

class EnemyHugDaemon : public Enemy {
public:
	EnemyHugDaemon( const Vector& pos );
	virtual ~EnemyHugDaemon( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
};

