#pragma once
#include "Enemy.h"

class EnemyGhoul : public Enemy {
public:
	EnemyGhoul( const Vector& pos );
	virtual ~EnemyGhoul( );
public:
	Chip getChip( ) const;
protected:
	void act( );
private:
	Vector _origin_pos;
};

