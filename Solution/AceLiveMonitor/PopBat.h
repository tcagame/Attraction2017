#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopBat : public Pop {
public:
	PopBat( const Vector& pos );
	virtual ~PopBat( );
public:
	void update( );
private:
	int _count;
	EnemyWeakPtr _enemy;
};

