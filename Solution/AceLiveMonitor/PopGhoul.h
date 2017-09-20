#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopGhoul : public Pop {
public:
	PopGhoul( const Vector& pos );
	virtual ~PopGhoul( );
public:
	void update( );
private:
	int _count;
	EnemyWeakPtr _enemy;
};

