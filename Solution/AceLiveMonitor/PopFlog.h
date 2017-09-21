#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopFlog : public Pop {
public:
	PopFlog( const Vector& pos );
	virtual ~PopFlog( );
public:
	void update( );
private:
	int _max_pop_time;
	int _count;
	EnemyWeakPtr _enemy;
};

