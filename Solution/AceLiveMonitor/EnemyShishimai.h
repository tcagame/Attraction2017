#pragma once
#include "Enemy.h"

class EnemyShishimai : public Enemy {
public:
	EnemyShishimai( const Vector& pos );
	virtual ~EnemyShishimai( );
public:
	Chip getChip( ) const;
protected:
	void act( );
private:
	Vector _origin_pos;
	bool _attack;
};

