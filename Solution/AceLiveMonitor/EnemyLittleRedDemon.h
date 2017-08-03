#pragma once
#include "Enemy.h"
class EnemyLittleRedDemon : public Enemy {
public:
	EnemyLittleRedDemon( const Vector& pos );
	virtual ~EnemyLittleRedDemon( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

