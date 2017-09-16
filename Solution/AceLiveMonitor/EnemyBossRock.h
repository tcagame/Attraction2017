#pragma once
#include "EnemyBoss.h"
class EnemyBossRock : public EnemyBoss {
public:
	EnemyBossRock( const Vector& pos );
	virtual ~EnemyBossRock( );
public:
	void setSynchronousData( int camera_pos ) const;
	void dropItem( );
protected:
	void act( );
};

