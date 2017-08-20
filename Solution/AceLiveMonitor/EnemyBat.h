#pragma once
#include "Enemy.h"

class EnemyBat : public Enemy {
public:
	EnemyBat( const Vector& pos );
	virtual ~EnemyBat( );
public:
	Chip getChip( ) const;
protected:
	void act( );
private:
	Vector _center;
};

