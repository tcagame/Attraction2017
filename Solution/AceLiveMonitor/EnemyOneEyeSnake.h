#pragma once
#include "Enemy.h"

class EnemyOneEyeSnake : public Enemy {
public:
	EnemyOneEyeSnake( const Vector& pos );
	virtual ~EnemyOneEyeSnake( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
private:
	Vector _before_pos;
	Vector _vec;
};

