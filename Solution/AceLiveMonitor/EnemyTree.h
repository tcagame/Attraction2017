#pragma once
#include "Enemy.h"

class EnemyTree : public Enemy {
public:
	EnemyTree( const Vector& pos );
	virtual ~EnemyTree( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
};