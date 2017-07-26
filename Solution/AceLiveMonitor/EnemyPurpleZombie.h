#pragma once
#include "Enemy.h"
class EnemyPurpleZombie : public Enemy {
public:
	EnemyPurpleZombie( const Vector& pos );
	virtual ~EnemyPurpleZombie( );
public:
	void getChipIndex( int& cx, int& cy ) const;
protected:
	void act( );
};

