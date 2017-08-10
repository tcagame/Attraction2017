#pragma once
#include "Enemy.h"
#include "smart_ptr.h"

PTR( Enemy );

class EnemyBranch : public Enemy {
public:
	EnemyBranch( const Vector& pos );
	virtual ~EnemyBranch( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

