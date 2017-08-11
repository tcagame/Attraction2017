#pragma once
#include "Enemy.h"

class EnemyMoth : public Enemy {
public:
	EnemyMoth( const Vector& pos );
	virtual ~EnemyMoth( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

