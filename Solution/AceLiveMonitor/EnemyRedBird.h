#pragma once
#include "Enemy.h"
class EnemyRedBird : public Enemy {
public:
	EnemyRedBird( const Vector& pos );
	virtual ~EnemyRedBird( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

