#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopRay : public Pop {
public:
	PopRay( const Vector& pos );
	virtual ~PopRay( );
public:
	void update( );
private:
	int _count;
	EnemyWeakPtr _enemy;
};

