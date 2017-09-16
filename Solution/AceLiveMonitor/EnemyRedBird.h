#pragma once
#include "Enemy.h"
class EnemyRedBird : public Enemy {
public:
	EnemyRedBird( const Vector& pos );
	virtual ~EnemyRedBird( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
};

