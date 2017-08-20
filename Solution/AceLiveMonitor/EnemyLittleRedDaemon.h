#pragma once
#include "Enemy.h"

class EnemyLittleRedDaemon : public Enemy {
public:
	EnemyLittleRedDaemon( const Vector& pos );
	virtual ~EnemyLittleRedDaemon( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

