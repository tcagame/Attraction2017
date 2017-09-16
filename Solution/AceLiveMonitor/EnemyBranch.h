#pragma once
#include "Enemy.h"
#include "smart_ptr.h"
#include "EnemyAttack.h"

PTR( Enemy );

class EnemyBranch : public EnemyAttack {
public:
	EnemyBranch( const Vector& pos );
	virtual ~EnemyBranch( );
public:
	void setSynchronousData( int camera_pos ) const;
protected:
	void act( );
};

