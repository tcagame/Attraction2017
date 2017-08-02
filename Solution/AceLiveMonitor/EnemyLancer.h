#pragma once
#include "Enemy.h"

class EnemyLancer : public Enemy {
public:
	EnemyLancer( const Vector& pos );
	virtual ~EnemyLancer( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

