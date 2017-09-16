#pragma once
#include "Enemy.h"

class EnemyWaterGhost : public Enemy {
public:
	EnemyWaterGhost( const Vector& pos );
	virtual ~EnemyWaterGhost( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
};

