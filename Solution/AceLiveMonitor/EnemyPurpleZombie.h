#pragma once
#include "Enemy.h"
class EnemyPurpleZombie : public Enemy {
public:
	EnemyPurpleZombie( const Vector& pos );
	virtual ~EnemyPurpleZombie( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
private:
	Vector _vec;
	Vector _before_pos;
};

