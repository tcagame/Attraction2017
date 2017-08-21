#pragma once
#include "Enemy.h"

class EnemyLittleRedDaemon : public Enemy {
public:
	EnemyLittleRedDaemon( const Vector& pos );
	virtual ~EnemyLittleRedDaemon( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
};

