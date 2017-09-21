#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopWaterGhost : public Pop {
public:
	PopWaterGhost( const Vector& pos );
	virtual ~PopWaterGhost( );
public:
	void update( );
private:
	int _count;
	int _max_pop_time;
	EnemyWeakPtr _enemy;
};

