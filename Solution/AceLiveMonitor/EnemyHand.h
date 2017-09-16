#pragma once
#include "Enemy.h"

class EnemyHand : public Enemy {
public:
	EnemyHand( const Vector& pos );
	virtual ~EnemyHand( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
};

