#pragma once
#include "EnemyBoss.h"


class EnemyBossBloodDaemon : public EnemyBoss {
public:
	EnemyBossBloodDaemon( const Vector& pos );
	virtual ~EnemyBossBloodDaemon( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
	void dropItem( );
protected:
	void act( );
};

