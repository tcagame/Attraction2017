#pragma once
#include "Enemy.h"

class EnemyTree : public Enemy {
public:
	EnemyTree( const Vector& pos );
	virtual ~EnemyTree( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};