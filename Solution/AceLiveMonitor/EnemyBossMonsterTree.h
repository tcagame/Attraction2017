#pragma once
#include "EnemyBoss.h"
#include "smart_ptr.h"

PTR( Enemy );

class EnemyBossMonsterTree : public EnemyBoss {
public:
	EnemyBossMonsterTree( const Vector& pos );
	virtual ~EnemyBossMonsterTree( );
public:
	void setSynchronousData( unsigned char type, int camera_pos ) const;
	void dropItem( );
protected:
	void act( );
private:
	EnemyPtr _branch;
};

