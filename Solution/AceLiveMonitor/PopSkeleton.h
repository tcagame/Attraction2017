#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopSkeleton : public Pop {
public:
	PopSkeleton( const Vector& pos );
	virtual ~PopSkeleton( );
public:
	void update( );
private:
	int _count;
	int _max_pop_time;
	EnemyWeakPtr _enemy;
};

