#pragma once
#include "Enemy.h"

class EnemyStone : public Enemy {
public:
	EnemyStone( const Vector& pos );
	virtual ~EnemyStone( );
public:
	void setSynchronousData( int camera_pos ) const;
	void damage( int force );
protected:
	void act( );
private:
	Vector _before_pos;
	Vector _vec;
};

