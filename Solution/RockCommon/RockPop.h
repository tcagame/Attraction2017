#pragma once
#include "smart_ptr.h"

PTR( RockEnemy );

class RockPop {
public:
	RockPop( RockEnemyPtr enemy );
	virtual ~RockPop( );
public:
	void update( );
	bool isFinished( ) const;
private:
	int _count;
	RockEnemyPtr _enemy;
};

