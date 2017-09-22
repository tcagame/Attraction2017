#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopTurtle : public Pop {
public:
	PopTurtle( const Vector& pos );
	virtual ~PopTurtle( );
public:
	void update( );
	EnemyWeakPtr _enemy;
};

