#pragma once
#include "EnemyAttack.h"

class EnemySeed : public EnemyAttack {
public:
	EnemySeed( const Vector& pos );
	virtual ~EnemySeed( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
protected:
	void act( );
};

