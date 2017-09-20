#pragma once
#include "Enemy.h"

class EnemyRay : public Enemy {
public:
	EnemyRay( const Vector& pos );
	virtual ~EnemyRay( );
public:
	void setSynchronousData( int camera_pos ) const;
	Vector getOverlappedPos( ) const;
protected:
	void act( );
};

