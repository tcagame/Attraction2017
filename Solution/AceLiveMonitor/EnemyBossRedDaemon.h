#pragma once
#include "EnemyBoss.h"

PTR( Enemy );

class EnemyBossRedDaemon : public EnemyBoss {
public:
	EnemyBossRedDaemon( const Vector& pos );
	virtual ~EnemyBossRedDaemon( );
public:
	Chip getChip( ) const;
	Chip getChip2( ) const;
	void dropItem( );
protected:
	void act( );
};

