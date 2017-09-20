#pragma once
#include "mathmatics.h"
#include "Pop.h"
#include "smart_ptr.h"

PTR( Enemy );

class PopPurpleZombie : public Pop {
public:
	PopPurpleZombie( const Vector& pos );
	virtual ~PopPurpleZombie( );
public:
	void update( );
private:
	int _count;
	EnemyWeakPtr _enemy;
};

