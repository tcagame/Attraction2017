#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopTree : public Pop {
public:
	PopTree( const Vector& pos );
	virtual ~PopTree( );
public:
	void update( );
private:
	int _count;
	EnemyWeakPtr _enemy;
};

