#pragma once
#include "Enemy.h"

class EnemyShishimai : public Enemy {
public:
	EnemyShishimai( const Vector& pos );
	virtual ~EnemyShishimai( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
private:
	Vector _origin_pos;
	bool _attack;
};

