#pragma once
#include "Enemy.h"

class EnemyWind : public Enemy {
public:
	EnemyWind( const Vector& pos );
	virtual ~EnemyWind( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
	void damage( int force );
private:
	int _count;
};

