#pragma once
#include "Enemy.h"

class EnemyHand : public Enemy {
public:
	EnemyHand( const Vector& pos );
	virtual ~EnemyHand( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

