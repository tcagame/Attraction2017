#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy )

class PopOneEyeSnake : public Pop {
public:
	PopOneEyeSnake( const Vector& pos );
	virtual ~PopOneEyeSnake( );
public:
	void update( );
private:
	int _count;
	int _max_pop_time;
	EnemyWeakPtr _enemy;
};

