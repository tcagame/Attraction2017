#pragma once
#include "Enemy.h"

class EnemyLittleRedDaemon : public Enemy {
public:
	EnemyLittleRedDaemon( const Vector& pos );
	virtual ~EnemyLittleRedDaemon( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
};

