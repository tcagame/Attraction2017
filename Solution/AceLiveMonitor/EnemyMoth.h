#pragma once
#include "Enemy.h"

class EnemyMoth : public Enemy {
public:
	EnemyMoth( const Vector& pos );
	virtual ~EnemyMoth( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
private:
	int _vy;
	int _dir;
};

