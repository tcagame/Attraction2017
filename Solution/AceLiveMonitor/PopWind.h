#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopWind : public Pop {
public:
	PopWind( const Vector& pos );
	virtual ~PopWind( );
public:
	void update( );
private:
	int _count;
	EnemyWeakPtr _enemy;
};

