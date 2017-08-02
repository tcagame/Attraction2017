#pragma once
#include "Enemy.h"
class EnemyNoFace : public Enemy {
public:
	EnemyNoFace( const Vector& pos );
	virtual ~EnemyNoFace( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

