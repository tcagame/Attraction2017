#pragma once
#include "Enemy.h"

class EnemyGreenZombie : public Enemy {
public:
	EnemyGreenZombie( const Vector& pos );
	virtual ~EnemyGreenZombie( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
private:
	Vector _before_pos;
};

