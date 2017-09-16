#pragma once
#include "EnemyAttack.h"

class EnemySeed : public EnemyAttack {
public:
	EnemySeed( const Vector& pos );
	virtual ~EnemySeed( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
};

