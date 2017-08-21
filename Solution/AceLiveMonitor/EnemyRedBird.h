#pragma once
#include "Enemy.h"
class EnemyRedBird : public Enemy {
public:
	EnemyRedBird( const Vector& pos );
	virtual ~EnemyRedBird( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
};

