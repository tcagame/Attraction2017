#pragma once
#include "EnemyAttack.h"

class EnemySeed : public EnemyAttack {
public:
	EnemySeed( const Vector& pos );
	virtual ~EnemySeed( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

