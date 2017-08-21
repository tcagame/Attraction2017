#pragma once
#include "Enemy.h"

class EnemyShell : public Enemy {
public:
	EnemyShell( const Vector& pos );
	virtual ~EnemyShell( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
};

