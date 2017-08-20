#pragma once
#include "Enemy.h"

class EnemyEyeDaemon : public Enemy {
public:
	EnemyEyeDaemon( const Vector& pos );
	virtual ~EnemyEyeDaemon( );
public:
	Chip getChip( ) const;
protected:
	void act( );
private:
	Vector _before_pos;
	bool _air_jump;
};

