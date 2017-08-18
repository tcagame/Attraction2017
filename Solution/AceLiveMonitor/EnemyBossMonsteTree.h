#pragma once
#include "EnemyBoss.h"
#include "smart_ptr.h"

PTR( Enemy );

class EnemyBossMonsteTree : public EnemyBoss {
public:
	EnemyBossMonsteTree( const Vector& pos );
	virtual ~EnemyBossMonsteTree( );
public:
	Chip getChip( ) const;
	void dropItem( );
protected:
	void act( );
private:
	EnemyPtr _branch;
};

