#pragma once
#include "EnemyAttack.h"

class EnemyHandAttack : public EnemyAttack {
public:
	EnemyHandAttack( const Vector& pos );
	virtual ~EnemyHandAttack( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

