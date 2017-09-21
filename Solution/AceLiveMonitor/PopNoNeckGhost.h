#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopNoNeckGhost : public Pop {
public:
	PopNoNeckGhost( const Vector& pos );
	virtual ~PopNoNeckGhost( );
public:
	void update( );
private:
	int _count;
	int _max_pop_time;
	EnemyWeakPtr _enemy;
};

