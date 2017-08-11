#pragma once
#include "Enemy.h"

class EnemyFlog : public Enemy {
public:
	EnemyFlog( const Vector& pos );
	virtual ~EnemyFlog( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

