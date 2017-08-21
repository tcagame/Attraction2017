#pragma once
#include "Enemy.h"

class EnemyArcherAttack : public Enemy {
public:
	EnemyArcherAttack( const Vector& pos );
	virtual ~EnemyArcherAttack();
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
};

