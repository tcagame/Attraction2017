#pragma once
#include "Enemy.h"

class EnemyFlog : public Enemy {
public:
	EnemyFlog( const Vector& pos );
	virtual ~EnemyFlog( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
private:
	Vector _vec;
};

