#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopGhost: public Pop {
public:
	PopGhost( const Vector& pos );
	virtual ~PopGhost( );
public:
	void update( );
private:
	int _count;
	EnemyWeakPtr _enemy;
};

