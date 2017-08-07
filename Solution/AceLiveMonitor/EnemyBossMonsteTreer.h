#pragma once
#include "EnemyBoss.h"
class EnemyBossMonsteTreer : public EnemyBoss {
public:
	EnemyBossMonsteTreer( const Vector& pos );
	virtual ~EnemyBossMonsteTreer( );
public:
	Chip getChip( ) const;
protected:
	void act( );
};

