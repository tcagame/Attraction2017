#pragma once
#include "EnemyBoss.h"

PTR( Enemy );

class EnemyBossRedDaemon : public EnemyBoss {
public:
	EnemyBossRedDaemon( const Vector& pos );
	virtual ~EnemyBossRedDaemon( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
	void dropItem( );
protected:
	void act( );
};

