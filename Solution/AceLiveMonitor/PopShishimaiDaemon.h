#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopShishimaiDaemon : public Pop {
public:
	PopShishimaiDaemon( const Vector& pos );
	virtual ~PopShishimaiDaemon( );
public:
	void update( );
private:
	int _count;
	int _max_pop_time;
	EnemyWeakPtr _enemy;
};

