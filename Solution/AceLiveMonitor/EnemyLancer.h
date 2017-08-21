#pragma once
#include "Enemy.h"

class EnemyLancer : public Enemy {
public:
	EnemyLancer( const Vector& pos );
	virtual ~EnemyLancer( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
};

