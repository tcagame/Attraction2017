#pragma once
#include "Enemy.h"

class EnemySkeleton : public Enemy {
public:
	EnemySkeleton( const Vector& pos );
	virtual ~EnemySkeleton( );
public:
	void setSynchronousData( int camera_pos ) const;
	Vector getOverlappedPos( ) const;
protected:
	void act( );
};

