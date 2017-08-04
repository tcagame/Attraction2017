#pragma once
#include "Enemy.h"

class EnemySkeleton : public Enemy {
public:
	EnemySkeleton( const Vector& pos );
	virtual ~EnemySkeleton( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

