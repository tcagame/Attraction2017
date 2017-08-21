#pragma once
#include "Enemy.h"

class EnemyRay : public Enemy {
public:
	EnemyRay( const Vector& pos );
	virtual ~EnemyRay( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
};

