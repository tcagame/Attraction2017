#pragma once
#include "Enemy.h"

class EnemyBat : public Enemy {
public:
	EnemyBat( const Vector& pos );
	virtual ~EnemyBat( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
private:
	Vector _center;
};

