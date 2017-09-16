#pragma once
#include "Enemy.h"

class EnemyTree : public Enemy {
public:
	EnemyTree( const Vector& pos );
	virtual ~EnemyTree( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
};