#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopMoth : public Pop {
public:
	PopMoth( const Vector& pos );
	virtual ~PopMoth( );
public:
	void update( );
private:
	int _count;
	EnemyWeakPtr _enemy;
};

