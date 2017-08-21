#pragma once
#include "EnemyBoss.h"
class EnemyBossRock : public EnemyBoss {
public:
	EnemyBossRock( const Vector& pos );
	virtual ~EnemyBossRock( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
	void dropItem( );
protected:
	void act( );
};

