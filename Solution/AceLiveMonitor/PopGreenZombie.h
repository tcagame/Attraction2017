#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopGreenZombie : public Pop {
public:
	PopGreenZombie( const Vector& pos );
	virtual ~PopGreenZombie( );
public:
	void update( );
private:
	int _count;
	int _max_pop_time;
	EnemyWeakPtr _enemy;
};

