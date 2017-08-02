#pragma once
#include "Enemy.h"

class EnemyWhiteMist : public Enemy {
public:
	EnemyWhiteMist( const Vector& pos );
	virtual ~EnemyWhiteMist( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

