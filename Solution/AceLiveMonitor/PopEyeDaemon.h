#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopEyeDaemon : public Pop {
public:
	PopEyeDaemon( const Vector& pos );
	virtual ~PopEyeDaemon( );
public:
	void update( );
private:
	int _max_pop_time;
	int _count;
	EnemyWeakPtr _enemy;
};

