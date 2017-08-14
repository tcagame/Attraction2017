#pragma once
#include "Enemy.h"

class EnemyCrocoSnake : public Enemy {
public:
	EnemyCrocoSnake( const Vector& pos );
	virtual ~EnemyCrocoSnake( );
public:
	Chip getChip( ) const;
protected:
	void act( );
private:
	Vector _before_pos;
	Vector _vec;
};

