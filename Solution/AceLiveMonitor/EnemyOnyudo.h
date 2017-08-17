#pragma once
#include "Enemy.h"

class EnemyOnyudo : public Enemy {
public:
	EnemyOnyudo( const Vector& pos );
	virtual ~EnemyOnyudo( );
public:
	Chip getChip( ) const;
protected:
	void act( );
private:
	Vector _vec;
	Vector _before_pos;
};

