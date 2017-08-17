#pragma once
#include "Enemy.h"

class EnemyGreenZombie : public Enemy {
public:
	EnemyGreenZombie( const Vector& pos );
	virtual ~EnemyGreenZombie( );
public:
	Chip getChip( ) const;
protected:
	void act( );
private:
	Vector _vec;
	Vector _before_pos;
};

