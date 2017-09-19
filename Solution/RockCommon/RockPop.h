#pragma once
#include "smart_ptr.h"

PTR( RockEnemy );

class RockPop {
public:
	RockPop( RockEnemyPtr enemy, bool moment );
	virtual ~RockPop( );
public:
	void update( );
	bool isFinished( ) const;
private:
	bool _pop;
	int _count;
	RockEnemyPtr _enemy;
};

