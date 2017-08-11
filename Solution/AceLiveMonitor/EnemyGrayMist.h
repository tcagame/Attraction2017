#pragma once
#include "Enemy.h"

class EnemyGrayMist : public Enemy {
public:
	EnemyGrayMist( const Vector& pos );
	virtual ~EnemyGrayMist( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

