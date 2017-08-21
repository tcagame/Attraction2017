#pragma once
#include "EnemyAttack.h"

class EnemyHandAttack : public EnemyAttack {
public:
	EnemyHandAttack( const Vector& pos );
	virtual ~EnemyHandAttack( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
};

