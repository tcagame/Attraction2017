#pragma once
#include "Enemy.h"

class EnemyShishimaiDaemon : public Enemy {
public:
	EnemyShishimaiDaemon( const Vector& pos );
	virtual ~EnemyShishimaiDaemon( );
public:
	Chip getChip( ) const;
protected:
	void act( );
private:
	bool _escape;
	Vector _befor_pos;
};

