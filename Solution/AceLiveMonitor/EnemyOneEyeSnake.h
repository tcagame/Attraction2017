#pragma once
#include "Enemy.h"

class EnemyOneEyeSnake : public Enemy {
public:
	EnemyOneEyeSnake( const Vector& pos );
	virtual ~EnemyOneEyeSnake( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

