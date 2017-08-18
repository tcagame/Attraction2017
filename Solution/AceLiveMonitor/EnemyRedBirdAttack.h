#pragma once
#include "EnemyAttack.h"
class EnemyRedBirdAttack : public EnemyAttack {
public:
	EnemyRedBirdAttack( const Vector& pos );
	virtual ~EnemyRedBirdAttack( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

