#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopLady : public Pop {
public:
	PopLady( const Vector& pos );
	virtual ~PopLady( );
public:
	void update( );
private:
	int _count;
	int _max_pop_time;
	EnemyWeakPtr _enemy;
};

