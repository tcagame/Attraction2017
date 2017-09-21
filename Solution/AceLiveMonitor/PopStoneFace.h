#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopStoneFace : public Pop {
public:
	PopStoneFace( const Vector& pos );
	virtual ~PopStoneFace( );
public:
	void update( );
private:
	int _count;
	int _max_pop_time;
	EnemyWeakPtr _enemy;
};

