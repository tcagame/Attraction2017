#pragma once
#include "Enemy.h"

class EnemyGrayMist : public Enemy {
public:
	EnemyGrayMist( const Vector& pos );
	virtual ~EnemyGrayMist( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
private:
	int _vy;
	int _dir;
};

