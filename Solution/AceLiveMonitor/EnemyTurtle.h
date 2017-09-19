#pragma once
#include "Enemy.h"

class EnemyTurtle : public Enemy {
public:
	EnemyTurtle( const Vector& pos );
	virtual ~EnemyTurtle( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
};

