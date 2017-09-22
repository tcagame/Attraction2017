#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy )

class PopStone : public Pop {
public:
	PopStone( const Vector& pos );
	virtual ~PopStone( );
public:
	void update( );
private:
	int _count;
	int _max_pop_time;
	EnemyWeakPtr _enemy;
};

