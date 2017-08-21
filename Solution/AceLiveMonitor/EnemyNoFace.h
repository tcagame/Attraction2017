#pragma once
#include "Enemy.h"
class EnemyNoFace : public Enemy {
public:
	EnemyNoFace( const Vector& pos );
	virtual ~EnemyNoFace( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
private:
	double _vec_x;
};

