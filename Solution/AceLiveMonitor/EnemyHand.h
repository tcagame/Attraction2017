#pragma once
#include "Enemy.h"

class EnemyHand : public Enemy {
public:
	EnemyHand( const Vector& pos );
	virtual ~EnemyHand( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
};

