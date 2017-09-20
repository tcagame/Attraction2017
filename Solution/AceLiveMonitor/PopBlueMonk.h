#pragma once
#include "Pop.h"
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopBlueMonk : public Pop {
public:
	PopBlueMonk( const Vector& pos );
	virtual ~PopBlueMonk( );
public:
	void update( );
private:
	int _count;
	EnemyWeakPtr _enemy;
};

